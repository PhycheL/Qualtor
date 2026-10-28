"""两条独立构建链的契约一致性、输入边界与编译单元隔离回归。"""
import copy
import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build_contract
import common

spec = importlib.util.spec_from_file_location(
    "product_build_contract", common.REPO / "agents/generator/build/contract.py")
product_contract = importlib.util.module_from_spec(spec)
spec.loader.exec_module(product_contract)


class BuildContractTest(unittest.TestCase):
    def setUp(self):
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        self.root = Path(tmp.name)
        for name in ("a.c", "a.cc", "support.cc", "support.c"):
            (self.root / name).write_text("/* fixture */\n")
        self.visible = [p.name for p in self.root.iterdir()]

    def test_both_contracts_accept_defaults_and_mixed_languages_without_mutating_task(self):
        build = {"support_sources": ["support.cc", "support.c"], "c_standard": "c99",
                 "defines": ["FEATURE", "LIMIT=8", "EPS=0.5", "MASK=0xFF"],
                 "compile_options": ["-fno-strict-aliasing", "-fsigned-char"]}
        before = copy.deepcopy(build)
        outputs = [m.validate_build(build, ["a.c"], self.visible, self.root)
                   for m in (build_contract, product_contract)]
        self.assertEqual(outputs[0], outputs[1])
        self.assertEqual(build, before)
        for module in (build_contract, product_contract):
            self.assertEqual(module.validate_build({}, ["a.cc"], self.visible, self.root)["support_sources"], [])

    def test_both_contracts_reject_unapproved_build_inputs(self):
        bad = [None, [], {"link_libraries": []}, {"support_sources": "support.cc"},
               {"support_sources": ["a.cc"]}, {"support_sources": ["missing.cc"]},
               {"support_sources": ["../a.cc"]}, {"support_sources": ["support.cc", "support.cc"]},
               {"defines": ["X;Y"]}, {"defines": ["X=$<CONFIG>"]}, {"defines": ["X=1", "X=2"]},
               {"defines": ["__cplusplus=202002L"]}, {"defines": ["X=\"path\""]},
               {"compile_options": ["-std=c++20"]}, {"compile_options": ["@args"]},
               {"compile_options": ["-fsigned-char", "-funsigned-char"]},
               {"c_standard": "gnu11"}, {"c_standard": 11}]
        for build in bad:
            for module in (build_contract, product_contract):
                with self.subTest(build=build, module=module.__name__), self.assertRaises(ValueError):
                    module.validate_build(build, ["a.cc"], self.visible, self.root)

    def test_c_requires_explicit_standard_and_support_must_be_visible(self):
        for module in (build_contract, product_contract):
            for targets, build, visible in [(["a.c"], {}, self.visible),
                                            (["a.cc"], {"support_sources": ["support.c"]}, self.visible),
                                            (["a.cc"], {"support_sources": ["support.cc"]}, ["a.cc"])]:
                with self.subTest(module=module.__name__), self.assertRaises(ValueError):
                    module.validate_build(build, targets, visible, self.root)

    def test_symlink_and_path_alias_cannot_make_support_a_second_target(self):
        (self.root / "link.cc").symlink_to(self.root / "a.cc")
        for path in ("link.cc", "./a.cc", "sub/../a.cc"):
            for module in (build_contract, product_contract):
                with self.subTest(path=path), self.assertRaises(ValueError):
                    module.validate_build({"support_sources": [path]}, ["a.cc"], self.visible + [path], self.root)

    def test_compile_manifest_checks_c_cpp_flags_and_instrumentation_boundaries(self):
        build = {"defines": ["FEATURE=1"], "compile_options": ["-fwrapv"], "c_standard": "c11"}
        targets, support, tests = ["/repo/a.c"], ["/repo/support.cc"], ["/product/tests/t.cc"]
        commands = [{"file": path, "arguments": ["cc", "-c", path, "-DFEATURE=1", "-fwrapv"] +
                    (["-std=c11", "--coverage"] if path in targets else
                     ["-std=c++11", "-include", "/cmake/cxx11_guard.h"])} for path in targets + support + tests]
        for module in (build_contract, product_contract):
            check = lambda values: module.compile_command_problems(values, targets, support, tests, build, "coverage")
            self.assertEqual(check(commands), [])
            for index, flag in ((0, "-std=c11"), (1, "-DFEATURE=1"), (2, "-fwrapv")):
                changed = copy.deepcopy(commands)
                changed[index]["arguments"].remove(flag)
                self.assertTrue(check(changed))
            for index, flag in ((0, "/cmake/cxx11_guard.h"), (1, "--coverage"),
                                (2, "-fpass-plugin=/usr/lib/mull-ir-frontend-19")):
                changed = copy.deepcopy(commands)
                changed[index]["arguments"].append(flag)
                self.assertTrue(check(changed))

    def test_existing_frozen_mull_hashes_remain_valid(self):
        for path in sorted(common.BENCHMARK.glob("*/task.json")):
            task = common.load_task(path.parent.name)
            baseline = common.load_baseline(task)
            if "build" not in task and baseline:
                with self.subTest(task=task["id"]):
                    self.assertEqual(common.sha256_text(common.mull_config_text(task)),
                                     baseline["mull"]["config_sha256"])
