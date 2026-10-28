"""宿主机集成测试：用本机编译器和 GoogleTest 1.12.1 把全部校准样本走一遍流水线（每个评两次）。

只检查不依赖 gcov 和 Mull 的部分：构建、发现与执行核对、稳定性、替换版本、重复评分一致。
需要设置 host_executor.py 中说明的环境变量，否则跳过。不能替代 Docker 容器中的校准。
"""
from pathlib import Path
import os
import shutil
import tempfile
import unittest
from unittest.mock import patch

import support  # noqa: F401
from audit import Audit
import calibrate
import common
import host_executor
import pipeline


class HostToolsTest(unittest.TestCase):
    def test_explicit_c_and_cpp_compilers_are_forwarded(self):
        env = {"QUALTOR_HOST_CMAKE": "/tools/cmake", "QUALTOR_HOST_NINJA": "/tools/ninja",
               "QUALTOR_HOST_GTEST": "/tools/gtest", "QUALTOR_HOST_CC": "/tools/gcc-14",
               "QUALTOR_HOST_CXX": "/tools/g++-14"}
        with patch.dict(os.environ, env, clear=True):
            tools = host_executor.HostExecutor().tools("gcc")
        self.assertEqual(tools["cc"], "/tools/gcc-14")
        self.assertEqual(tools["cxx"], "/tools/g++-14")
        env.pop("QUALTOR_HOST_CC")
        env.pop("QUALTOR_HOST_CXX")
        with patch.dict(os.environ, env, clear=True):
            tools = host_executor.HostExecutor().tools("gcc")
        self.assertEqual(tools["cc"], "cc")
        self.assertEqual(tools["cxx"], "c++")


@unittest.skipUnless(host_executor.available(), "未设置宿主机工具链环境变量")
class HostIntegrationTest(unittest.TestCase):
    def test_calibration_samples_on_host(self):
        task = common.load_task("gildedrose-update-quality")
        samples = calibrate.load_samples(task["id"])
        executor = host_executor.HostExecutor()
        out_root = Path(tempfile.mkdtemp(prefix="qualtor-host-calibration-"))
        try:
            results = {}
            for sid, sample in samples.items():
                rounds = []
                for index in (1, 2):
                    out = out_root / sid / f"round-{index}"
                    rounds.append(pipeline.assess_product(executor, task, sample["dir"] / "final", out,
                                                         {"calibration_sample": sid, "round": index},
                                                         Audit(out_root / sid / f"round-{index}-host"),
                                                         sample["dir"] / "generation" / "cost.json"))
                results[sid] = rounds
            report = calibrate.evaluate(task, samples, results, executor.capabilities)
            failures = {sid: e["problems"] for sid, e in report["samples"].items() if e["problems"]}
            self.assertEqual(failures, {})
        finally:
            shutil.rmtree(out_root)


if __name__ == "__main__":
    unittest.main()
