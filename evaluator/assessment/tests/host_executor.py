"""宿主机辅助检查用的执行器：直接在本机运行 container_steps.py，不用 Docker。

只用于评测模块自身的集成测试，不能产生正式评分：本机编译器不是固定版本，也没有 gcov 和 Mull，
所以覆盖率（步骤 5）和变异测试（步骤 6）会跳过。需要以下环境变量：
- QUALTOR_HOST_CMAKE、QUALTOR_HOST_NINJA：CMake 与 Ninja 可执行文件；
- QUALTOR_HOST_GTEST：GoogleTest 1.12.1 的安装前缀；
- QUALTOR_HOST_CC、QUALTOR_HOST_CXX（可选）：C/C++ 编译器，分别默认 cc、c++。
"""
import json
import os
from pathlib import Path
import subprocess
import sys

ASSESSMENT = Path(__file__).resolve().parents[1]
ENV_KEYS = ("QUALTOR_HOST_CMAKE", "QUALTOR_HOST_NINJA", "QUALTOR_HOST_GTEST")


def available():
    return all(os.environ.get(k) for k in ENV_KEYS)


class HostExecutor:
    mode = "local"
    capabilities = {"coverage": False, "mull": False}

    def __init__(self):
        self.images = {"host": {"tag": "host-toolchain", "id": "host", "platform": sys.platform}}

    @staticmethod
    def at(name, host_path):
        return str(Path(host_path).resolve()) if name != "assessment" else str(ASSESSMENT)

    def tools(self, toolchain):
        return {"cmake": os.environ["QUALTOR_HOST_CMAKE"], "make_program": os.environ["QUALTOR_HOST_NINJA"],
                "gtest_prefix": os.environ["QUALTOR_HOST_GTEST"], "cc": os.environ.get("QUALTOR_HOST_CC", "cc"),
                "cxx": os.environ.get("QUALTOR_HOST_CXX", "c++")}

    def run_phase(self, label, toolchain, mounts, env, job, out_host, timeout, audit):
        out_host = Path(out_host)
        out_host.mkdir(parents=True, exist_ok=True)
        (out_host / "job.json").write_text(json.dumps(job, ensure_ascii=False, indent=2) + "\n")
        completed = subprocess.run([sys.executable, "-B", str(ASSESSMENT / "container_steps.py"), "--job",
                                    str(out_host / "job.json")], env=dict(os.environ, **env),
                                   capture_output=True, text=True, timeout=timeout)
        (out_host / "executor.stdout.log").write_text(completed.stdout)
        (out_host / "executor.stderr.log").write_text(completed.stderr)
        step_path = out_host / "step.json"
        if not step_path.is_file():
            return {"status": "infra_error", "reason": "phase_no_output", "container_exit_code": completed.returncode}
        step = json.loads(step_path.read_text())
        step["container_exit_code"] = completed.returncode
        return step
