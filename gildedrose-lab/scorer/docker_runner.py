"""在固定版本的工具链镜像里执行评分阶段。隔离参数与工具链验收（toolchains.py）一致。"""
import itertools
import json
import os
from pathlib import Path
import sys
import threading

from common import LAB, SCORER, SCRIPTS, write_json

sys.path.insert(0, str(LAB))
from toolchains import IMAGES  # noqa: E402  镜像标签只在 toolchains.py 维护一份


class DockerError(RuntimeError):
    pass


class DockerExecutor:
    """每个阶段启动一个全新的容器：禁网、只读根文件系统、资源受限、非 root、无附加 capabilities。"""

    mode = "docker"
    capabilities = {"coverage": True, "mull": True}

    def __init__(self, audit, evidence_dir, run_tag):
        self.audit = audit
        self.run_tag = run_tag.lower()
        self._counter = itertools.count(1)
        self._lock = threading.Lock()
        endpoint = self._call("docker-endpoint", ["docker", "context", "inspect", "--format",
                                                  "{{.Endpoints.docker.Host}}"]).strip()
        client = Path(evidence_dir) / "docker-client"
        client.mkdir(parents=True, exist_ok=True)
        write_json(client / "config.json", {"auths": {}, "cliPluginsExtraDirs": [str(Path.home() / ".docker/cli-plugins")]})
        self.docker = ["docker", "--config", str(client), "--host", endpoint]
        self._call("docker-version", self.docker + ["version"])
        self.images = {}
        for toolchain, tag in IMAGES.items():
            record = json.loads(self._call(f"inspect-{toolchain}-image", self.docker + ["image", "inspect", tag]))[0]
            platform = f"{record['Os']}/{record['Architecture']}"
            if platform not in ("linux/arm64", "linux/amd64"):
                raise DockerError(f"不支持的镜像平台：{platform}")
            self.images[toolchain] = {"tag": tag, "id": record["Id"], "platform": platform}
        write_json(Path(evidence_dir) / "images.json", self.images)

    def _call(self, stage, command, timeout=180, audit=None):
        result = (audit or self.audit).run(stage, command, timeout=timeout)
        if result["returncode"] or result["timed_out"]:
            raise DockerError(f"{stage} failed; see {result['stderr_log']}")
        return result["stdout"]

    @staticmethod
    def at(name, host_path):
        """挂载点在容器内的路径。"""
        return "/" + name

    def tools(self, toolchain):
        return {}

    def run_phase(self, label, toolchain, mounts, env, job, out_host, timeout, audit):
        out_host = Path(out_host)
        out_host.mkdir(parents=True, exist_ok=True)
        (out_host / "step.json").unlink(missing_ok=True)
        write_json(out_host / "job.json", job)
        with self._lock:
            name = f"qs-{self.run_tag}-{next(self._counter):04d}"[:63]
        image = self.images[toolchain]
        command = self.docker + ["create", "--name", name, "--platform", image["platform"],
                                 "--network", "none", "--cpus", "2", "--memory", "2g", "--pids-limit", "256",
                                 "--cap-drop", "ALL", "--security-opt", "no-new-privileges", "--read-only",
                                 "--tmpfs", "/tmp:rw,nosuid,nodev,size=256m,mode=1777",
                                 "--user", f"{os.getuid()}:{os.getgid()}", "-e", "PYTHONDONTWRITEBYTECODE=1"]
        for key, value in sorted(env.items()):
            command += ["-e", f"{key}={value}"]
        expected = {"/scorer": (SCORER, True), "/scripts": (SCRIPTS, True)}
        expected.update({"/" + n: (Path(h), ro) for n, (h, ro) in mounts.items()})
        expected["/out"] = (out_host, False)
        for target, (source, readonly) in sorted(expected.items()):
            command += ["--mount", f"type=bind,source={source},target={target}" + (",readonly" if readonly else "")]
        command += [image["id"], "python3", "/scorer/container_steps.py", "--job", "/out/job.json"]
        self._call(f"{label}-create", command, audit=audit)
        try:
            before = json.loads(self._call(f"{label}-inspect-before", self.docker + ["inspect", name], audit=audit))[0]
            write_json(out_host / "container-before.json", before)
            actual = {m["Destination"]: m for m in before["Mounts"]}
            if (before["HostConfig"]["NetworkMode"] != "none" or not before["HostConfig"]["ReadonlyRootfs"]
                    or set(actual) != set(expected)
                    or any(actual[t]["RW"] == readonly for t, (_, readonly) in expected.items())):
                raise DockerError(f"{label}: 容器隔离或挂载配置不正确")
            execution = audit.run(f"{label}-start", self.docker + ["start", "--attach", name],
                                  timeout=timeout, echo=False)
            after = json.loads(self._call(f"{label}-inspect-after", self.docker + ["inspect", name], audit=audit))[0]
            write_json(out_host / "container-after.json", after)
            if after["State"]["Running"]:
                self._call(f"{label}-stop", self.docker + ["stop", "--time", "5", name], audit=audit)
        finally:
            self._call(f"{label}-remove", self.docker + ["rm", "--force", name], audit=audit)
        step_path = out_host / "step.json"
        if execution["timed_out"] or not step_path.is_file():
            return {"status": "infra_error", "reason": "phase_timeout" if execution["timed_out"] else "phase_no_output",
                    "container_exit_code": after["State"]["ExitCode"]}
        step = json.loads(step_path.read_text())
        step["container_exit_code"] = after["State"]["ExitCode"]
        step["image"] = image["id"]
        return step
