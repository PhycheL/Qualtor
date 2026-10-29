"""只负责固定 GCC 镜像内的普通编译和执行，不接收模型凭证或评分材料。"""
import json
import os
from pathlib import Path
import uuid

from common.audit import Audit
from generator.support import AGENTS, read_json, write_json
from generator.build.contract import task_environment, environment_tag, environment_find_packages
from generator.build.environment import isolated_run


def docker_command(audit, evidence, cancel=None):
    endpoint = audit.run("docker-endpoint", ["docker", "context", "inspect", "--format", "{{.Endpoints.docker.Host}}"], cancel=cancel)
    if endpoint["returncode"]:
        raise RuntimeError(f"Docker 不可用，见 {endpoint['stderr_log']}")
    client = Path(evidence) / "docker-client"
    write_json(client / "config.json", {"auths": {}, "cliPluginsExtraDirs": [str(Path.home() / ".docker/cli-plugins")]})
    return ["docker", "--config", str(client), "--host", endpoint["stdout"].strip()]


class DockerCompiler:
    def __init__(self, record, cancel=None, task=None):
        self.record = Path(record)
        self.cancel = cancel
        self.audit = Audit(self.record / "evidence/docker")
        self.command = docker_command(self.audit, self.record / "evidence", cancel)
        tag = read_json(AGENTS / "toolchains/images.json")["gcc"]
        item = json.loads(self.call("inspect-gcc", self.command + ["image", "inspect", tag]))[0]
        self.recipe = None
        selected = task_environment((task or {}).get('build', {}))
        if selected:
            self.recipe, digest = selected
            base = item
            tag = environment_tag(self.recipe, digest, 'gcc')
            item = json.loads(self.call('inspect-environment-gcc', self.command + ['image', 'inspect', tag]))[0]
            layers = base.get('RootFS', {}).get('Layers', [])
            if (item.get('Config', {}).get('Labels', {}).get('org.qualtor.environment.recipe-sha256') != digest
                    or (item['Os'], item['Architecture']) != (base['Os'], base['Architecture'])
                    or item.get('RootFS', {}).get('Layers', [])[:len(layers)] != layers):
                raise ValueError('环境镜像配方、架构或基础层不匹配')
        self.image = {"tag": tag, "id": item["Id"], "platform": f"{item['Os']}/{item['Architecture']}"}
        if self.image["platform"] not in ("linux/arm64", "linux/amd64"):
            raise ValueError("GCC 镜像平台必须为 linux/arm64 或 linux/amd64")
        if selected:
            self.image['environment'] = {'name': self.recipe['name'], 'recipe_sha256': digest, 'gcc_image_id': self.image['id']}
            self.preflight_environment()
        write_json(self.record / "toolchain.json", self.image)

    def preflight_environment(self):
        directory = self.record / 'evidence/environment-input'
        directory.mkdir(parents=True)
        cmake = ('cmake_minimum_required(VERSION 3.20)\nproject(environment_preflight LANGUAGES CXX)\n'
                 + environment_find_packages(self.recipe))
        for target in self.recipe['libraries']:
            cmake += f'if(NOT TARGET {target})\n  message(FATAL_ERROR "Missing {target}")\nendif()\n'
        (directory / 'CMakeLists.txt').write_text(cmake)
        write_json(directory / 'recipe.json', self.recipe)
        program = '''import json,subprocess
recipe=json.load(open('/check/recipe.json'))
for name,version in recipe['packages'].items():
    actual=subprocess.check_output(['dpkg-query','-W','-f=${Version}',name]).decode()
    if actual != version: raise RuntimeError('Environment package mismatch: '+name)
subprocess.run(['cmake','-S','/check','-B','/tmp/preflight','-G','Ninja',
                '-DCMAKE_PREFIX_PATH='+';'.join(['/opt/googletest']+recipe['cmake_prefix_path'])],check=True)
'''
        isolated_run(self.audit, self.command, self.image, ['python3', '-c', program],
                     self.record / 'evidence/environment-container', {'/check': (directory, True)}, cancel=self.cancel)

    def call(self, stage, command, audit=None, cleanup=False):
        result = (audit or self.audit).run(stage, command, timeout=15 if cleanup else 180,
                                         cancel=None if cleanup else self.cancel)
        if result["returncode"] or result["timed_out"] or result["cancelled"]:
            raise RuntimeError(f"{stage} 失败；见 {result['stderr_log']}")
        return result["stdout"]

    def build(self, attempt, task):
        attempt = Path(attempt)
        output = attempt / "output"
        output.mkdir(mode=0o700)
        inputs = attempt / "input"
        projected = {k: v for k, v in task.items() if k != "source_root"}
        if self.recipe:
            projected['_environment_recipe'] = self.recipe
        write_json(inputs / "task.json", projected)
        audit = Audit(attempt / "docker")
        name = "qg-build-" + uuid.uuid4().hex[:16]
        command = self.command + ["create", "--name", name, "--platform", self.image["platform"],
                   "--network", "none", "--cpus", "2", "--memory", "2g", "--pids-limit", "256",
                   "--read-only", "--user", "0:0", "--cap-drop", "ALL", "--security-opt", "no-new-privileges",
                   "--tmpfs", "/tmp:rw,exec,nosuid,nodev,size=512m,mode=1777",
                   "--tmpfs", "/private:rw,nosuid,nodev,size=1m,mode=700,uid=0,gid=0",
                   "-e", "PYTHONDONTWRITEBYTECODE=1", "-e", "PYTHONPATH=/helpers:/builder"]
        # root 只运行可信监督代码；编译器和生成的测试降权，不能修改 /out 内的审计结果。
        for cap in ("CHOWN", "DAC_OVERRIDE", "FOWNER", "KILL", "SETUID", "SETGID"):
            command += ["--cap-add", cap]
        mounts = {"/project": (self.record / "workspace/project", True),
                  "/product": (attempt / "product", True), "/input": (inputs, True),
                  "/builder": (AGENTS / "generator/build", True), "/helpers": (AGENTS / "common", True),
                  "/cmake": (AGENTS / "toolchains/cmake", True), "/private/output": (output, False)}
        for target, (source, readonly) in mounts.items():
            if "," in str(source):
                raise ValueError("Docker 挂载路径不能含逗号")
            command += ["--mount", f"type=bind,source={source},target={target}" + (",readonly" if readonly else "")]
        command += [self.image["id"], "python3", "/builder/container_build.py"]
        try:
            self.call("create-build", command, audit)
            actual = json.loads(self.call("inspect-build", self.command + ["inspect", name], audit))[0]
            write_json(attempt / "container.json", actual)
            mounted = {m["Destination"]: m for m in actual["Mounts"]}
            if (set(mounted) != set(mounts) or any(mounted[t]["RW"] == ro for t, (_, ro) in mounts.items())
                    or actual["HostConfig"]["NetworkMode"] != "none" or not actual["HostConfig"]["ReadonlyRootfs"]):
                raise ValueError("编译容器的只读挂载或隔离配置不正确")
            executed = audit.run("build", self.command + ["start", "--attach", name], timeout=1800, cancel=self.cancel)
            if executed["cancelled"]:
                raise RuntimeError("编译已取消")
            state = json.loads(self.call("build-exit", self.command + ["inspect", "--format", "{{json .State}}", name], audit))
            write_json(attempt / "container-exit.json", state)
            if executed["returncode"] or executed["timed_out"] or state["ExitCode"] or not (output / "result.json").is_file():
                raise RuntimeError(f"编译容器执行故障，见 {attempt / 'docker'}")
            return read_json(output / "result.json")
        finally:
            # create 可能在 Docker 服务端完成后才收到取消；按预先分配的名字清理。
            removed = audit.run("remove-build", self.command + ["rm", "--force", name], timeout=15)
            if (removed["returncode"] or removed["timed_out"]) and "No such container" not in removed["stderr"]:
                raise RuntimeError(f"编译容器清理失败，见 {removed['stderr_log']}")
