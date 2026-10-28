"""产品接口与宿主机运行边界回归测试。Docker 路径由独立产品验收验证。"""
import json
import os
from pathlib import Path
import re
import shutil
import signal
import subprocess
import sys
import tempfile
import time
import unittest
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from common import audit
from generator import config as host
from generator.support import write_json, tree_hash, dependency_hash
from generator.config import load_config
from generator.cost import extract, add_costs
from generator.build import container_build as build_service
from generator.runtime import launch
HERE = Path(__file__).resolve().parent

def alive(pid):
    try: os.kill(pid, 0)
    except ProcessLookupError: return False
    return True

class CostTest(unittest.TestCase):
    def test_first_cutoff_and_complete_messages_only(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            write_json(root / "generation.json", {"started_at": 1, "first_at": 2.5, "ended_at": 5, "repair_rounds": 1})
            logs = root / "logs/sessions"
            logs.mkdir(parents=True)
            messages = [{"type": "message", "message": {"role": "assistant", "timestamp": timestamp,
                        "usage": {"input": 10, "output": 5, "cacheRead": 4, "cacheWrite": 2, "cost": {"total": .25}}}}
                        for timestamp in (2000, 3000, 4000)]
            messages.insert(1, {"type": "message_update", "message": messages[0]["message"]})
            (logs / "session.jsonl").write_text("\n".join(json.dumps(m) for m in messages))
            result = extract(root)
            self.assertEqual(result["first"]["model_calls"], 1)
            self.assertEqual(result["final"]["model_calls"], 3)
            self.assertEqual(result["first"]["tokens"]["cache_read"], 4)
            self.assertEqual(result["final"]["usd"], .75)
            self.assertEqual(result["first"]["repair_rounds"], 0)
            self.assertIsNone(extract(root, priced=False)["final"]["usd"])
            self.assertEqual(add_costs(result["first"], [result["final"]])["model_calls"], 4)

class ConfigTest(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.env_file = self.root / "agents/.env"
        self.config = {"provider": "test", "model": "test", "thinking": "max", "api": "openai-completions",
                       "base_url_env": "QUALTOR_API_BASE_URL", "api_key_env": "QUALTOR_API_KEY"}
        write_json(self.root / "agents/configs/default/config.json", self.config)
        for target, value in (("generator.config.AGENTS", self.root / "agents"),):
            patcher = patch(target, value)
            patcher.start()
            self.addCleanup(patcher.stop)
        environment = patch.dict(os.environ, {"QUALTOR_API_BASE_URL": "https://stale.invalid/v1",
                                             "QUALTOR_API_KEY": "stale-shell-secret"})
        environment.start()
        self.addCleanup(environment.stop)

    def test_root_dotenv_overrides_shell_without_exporting_other_settings(self):
        self.env_file.write_text("# 本地配置\nQUALTOR_API_BASE_URL=https://model.invalid/v1\n"
                                 "QUALTOR_API_KEY=local-test-secret\nPATH=/untrusted\n", encoding="utf-8")
        original_path = os.environ.get("PATH")
        # 当前工作目录不是临时仓库，仍必须从仓库根目录读取。
        config, snapshot = load_config("default")
        self.assertEqual(config["base_url"], "https://model.invalid/v1")
        self.assertEqual(os.environ["QUALTOR_API_KEY"], "local-test-secret")
        self.assertEqual(os.environ["PATH"], original_path)
        self.assertNotIn("local-test-secret", json.dumps(snapshot))

    def test_missing_file_or_value_does_not_fall_back_to_shell(self):
        with self.assertRaisesRegex(ValueError, r"缺少.*\.env"):
            load_config("default")
        for suffix in ("", "QUALTOR_API_KEY=\n", "QUALTOR_API_KEY='  '\n"):
            with self.subTest(suffix=suffix):
                self.env_file.write_text("QUALTOR_API_BASE_URL=https://model.invalid/v1\n" + suffix)
                with self.assertRaisesRegex(ValueError, "QUALTOR_API_KEY"):
                    load_config("default")

    def test_comments_quotes_and_literal_special_characters(self):
        secret = r"literal#key=with${NO_INTERPOLATION}\backslash"
        for quote in ("", "'", '"'):
            with self.subTest(quote=quote):
                self.env_file.write_text("\ufeff# 配置\nexport QUALTOR_API_BASE_URL = 'https://model.invalid/v1' # 地址\n"
                                         f"QUALTOR_API_KEY={quote}{secret}{quote} # 密钥\n", encoding="utf-8")
                load_config("default")
                self.assertEqual(os.environ["QUALTOR_API_KEY"], secret)

    def test_invalid_dotenv_fails_without_disclosing_values(self):
        secret = "local-test-secret"
        for invalid in (f"{secret}\n", f"QUALTOR_API_KEY='{secret}\n",
                        f"QUALTOR_API_KEY={secret}\nQUALTOR_API_KEY=duplicate\n",
                        f"QUALTOR_API_KEY={secret}\0\n"):
            with self.subTest(invalid=invalid):
                self.env_file.write_text(invalid)
                with self.assertRaisesRegex(ValueError, r"\.env 第 \d+ 行") as caught:
                    load_config("default")
                self.assertNotIn(secret, str(caught.exception))
                self.assertEqual(os.environ["QUALTOR_API_KEY"], "stale-shell-secret")

class AuditLeftoverProcessTest(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.audit = audit.Audit(Path(temporary.name))

    def test_background_child_holding_stdout_is_killed(self):
        # 测试进程留下一个继承了 stdout 的后台进程；修复前这里会一直等到它结束。
        code = "import subprocess,sys; p=subprocess.Popen(['sleep','60']); print(p.pid, flush=True)"
        started = time.monotonic()
        result = self.audit.run("leftover", [sys.executable, "-c", code], timeout=30)
        self.assertLess(time.monotonic() - started, audit.DRAIN_GRACE_SECONDS)
        self.assertEqual(result["returncode"], 0)
        self.assertFalse(result["output_incomplete"])
        child = int(result["stdout"].split()[0])
        time.sleep(0.2)
        self.assertFalse(alive(child) and Path(f"/proc/{child}").exists(), "后台进程应已被结束")

    def test_child_escaping_process_group_does_not_block_forever(self):
        code = ("import subprocess,sys; p=subprocess.Popen(['sleep','60'], start_new_session=True); "
                "print(p.pid, flush=True)")
        with patch.object(audit, "DRAIN_GRACE_SECONDS", 1):
            started = time.monotonic()
            result = self.audit.run("escaped", [sys.executable, "-c", code], timeout=30)
            elapsed = time.monotonic() - started
        try:
            self.assertLess(elapsed, 10)
            self.assertTrue(result["output_incomplete"])
            self.assertEqual(result["returncode"], 0)
        finally:
            pid = re.search(r"\d+", result["stdout"] or "")
            if pid:
                try:
                    os.kill(int(pid.group()), signal.SIGKILL)
                except ProcessLookupError:
                    pass

class BuildServiceTest(unittest.TestCase):
    def test_feedback_lists_every_failure_before_details(self):
        outcomes = {f"Suite.Test{i:03d}": {"outcome": "passed"} for i in range(300)}
        for i in (5, 150, 299):
            outcomes[f"Suite.Test{i:03d}"] = {"outcome": "failed"}
        outcomes["Suite.Timeout"] = {"outcome": "timed_out"}
        details = {name: "x" * 5000 + "\n" for name in outcomes}
        text = build_service.feedback_text(outcomes, details)
        self.assertLessEqual(len(text), build_service.FEEDBACK_LIMIT)
        self.assertTrue(text.startswith("测试结果：共 301 个，通过 297 个，未通过 4 个。"))
        for name in ("Suite.Test005", "Suite.Test150", "Suite.Test299", "Suite.Timeout"):
            self.assertIn(f"- {name}:", text)
        self.assertIn("已截断", text)
        self.assertNotIn("Suite.Test006", text)  # 通过的测试不逐个列出

    def test_all_passed_feedback(self):
        text = build_service.feedback_text({"S.A": {"outcome": "passed"}}, {"S.A": "ok"})
        self.assertIn("全部通过", text)
        self.assertNotIn("失败详情", text)

    def test_kill_uid_only_kills_matching_processes(self):
        sleeper = subprocess.Popen(["sleep", "60"])
        self.addCleanup(lambda: sleeper.poll() is None and sleeper.kill())
        with tempfile.TemporaryDirectory() as tmp:
            proc = Path(tmp)
            (proc / str(sleeper.pid)).mkdir()
            (proc / "self").mkdir()
            self.assertEqual(build_service.kill_uid(os.getuid() + 12345, proc), [])
            self.assertIsNone(sleeper.poll())
            self.assertEqual(build_service.kill_uid(os.getuid(), proc), [sleeper.pid])
        sleeper.wait(timeout=5)
        self.assertEqual(sleeper.returncode, -signal.SIGKILL)

class WatchdogTest(unittest.TestCase):
    class Service:
        busy = False
        last_activity = 0.0

    def test_build_in_progress_pauses_watchdog(self):
        service = self.Service()
        self.assertEqual(launch.stalled_for(1000.0, 10.0, service), 990.0)
        service.busy = True
        self.assertEqual(launch.stalled_for(1000.0, 10.0, service), 0.0)

    def test_build_end_counts_as_activity(self):
        service = self.Service()
        service.last_activity = 900.0
        self.assertEqual(launch.stalled_for(1000.0, 10.0, service), 100.0)

    def test_copy_regular_skips_links_and_special_files(self):
        with tempfile.TemporaryDirectory() as tmp:
            source, target = Path(tmp) / "src", Path(tmp) / "dst"
            (source / "sub").mkdir(parents=True)
            (source / "a.cc").write_text("a")
            (source / "sub/b.h").write_text("b")
            os.symlink("/etc/passwd", source / "link.cc")
            os.mkfifo(source / "pipe")
            launch.copy_regular(source, target)
            self.assertEqual(sorted(str(p.relative_to(target)) for p in target.rglob("*")), ["a.cc", "sub", "sub/b.h"])

class PiRuntimeHashTest(unittest.TestCase):
    def test_dependency_changes_alter_runtime_hash_only(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "packages/a/node_modules/dep").mkdir(parents=True)
            (root / "packages/a/index.ts").write_text("source")
            dependency = root / "packages/a/node_modules/dep/index.js"
            dependency.write_text("module.exports = 1;")
            source, runtime = tree_hash(root), dependency_hash(root)
            dependency.write_text("module.exports = 'tampered';")
            self.assertEqual(tree_hash(root), source)
            self.assertNotEqual(dependency_hash(root), runtime)

class GuardNodeTest(unittest.TestCase):
    def test_guard_rules(self):
        node = shutil.which("node")
        if not node:
            self.skipTest("本机没有 node")
        version = subprocess.run([node, "--version"], capture_output=True, text=True).stdout.strip().lstrip("v")
        if tuple(int(x) for x in version.split(".")[:2]) < (23, 6):
            self.skipTest(f"node {version} 不能原生运行 .ts")
        result = subprocess.run([node, "--test", *map(str, sorted(HERE.glob("*.test.mjs")))], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout[-3000:] + result.stderr[-2000:])

class FeedbackTest(unittest.TestCase):
    def test_failure_list_larger_than_limit_is_preserved(self):
        outcomes = {f"LargeSuite.LongFailureName{i:04d}": {"outcome": "failed"} for i in range(500)}
        text = build_service.feedback_text(outcomes, {name: "detail" * 100 for name in outcomes})
        for name in outcomes:
            self.assertIn(f"- {name}: failed\n", text)
        self.assertIn("已截断", text)

class PublicTaskTest(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        (self.root / "source").mkdir()
        (self.root / "source/a.cc").write_text("int value() { return 1; }\n")
        self.path = self.root / "task.json"
        self.task = {"id": "t", "title": "test", "source_root": "source", "target_sources": ["a.cc"],
                     "include_dirs": ["."], "visible_files": ["a.cc"], "allowed_test_files": ["tests/*.cc"],
                     "budget": {"repair_rounds": 3}, "test_timeout_seconds": 5}

    def load(self):
        from generator.task import load_task
        write_json(self.path, self.task)
        return load_task(self.path)

    def test_relative_source_is_based_on_task_file(self):
        self.assertEqual(self.load()["source_root"], str((self.root / "source").resolve()))

    def test_hidden_scoring_fields_rejected(self):
        for key in ("hidden", "variants", "scoring_domain"):
            with self.subTest(key=key):
                self.task[key] = {}
                with self.assertRaisesRegex(ValueError, "未知字段"):
                    self.load()
                del self.task[key]

    def test_optional_build_is_public_and_c_source_is_supported(self):
        from generator.task import task_text
        (self.root / "source/helper.c").write_text("int helper(void) { return 2; }\n")
        self.task["visible_files"].append("helper.c")
        self.task["build"] = {"support_sources": ["helper.c"], "c_standard": "c11",
                              "defines": ["FEATURE=2"], "compile_options": ["-fwrapv"]}
        task = self.load()
        self.assertEqual(task["build"], self.task["build"])
        self.assertIn("FEATURE=2", task_text(task))
        self.task["build"]["hidden"] = "reference_tests"
        with self.assertRaises(ValueError):
            self.load()

    def test_visible_path_escape_and_symlink_parent_rejected(self):
        for value in ("../secret.cc", "/etc/passwd", "a.cc;injected.cc"):
            self.task["visible_files"] = [value]
            with self.subTest(value=value), self.assertRaises(ValueError):
                self.load()
        (self.root / "source/link").symlink_to(self.root, target_is_directory=True)
        self.task["visible_files"] = ["link/task.json"]
        with self.assertRaisesRegex(ValueError, "符号链接"):
            self.load()

    def test_invalid_budgets_and_timeouts_rejected(self):
        for budget in (-1, True, "3"):
            self.task["budget"]["repair_rounds"] = budget
            with self.subTest(budget=budget), self.assertRaises(ValueError):
                self.load()
        self.task["budget"]["repair_rounds"] = 3
        for timeout in (0, -1, True, float("inf"), float("nan")):
            self.task["test_timeout_seconds"] = timeout
            with self.subTest(timeout=timeout), self.assertRaises(ValueError):
                self.load()

    def test_target_must_be_visible_and_output_must_stay_in_tests(self):
        self.task["target_sources"] = ["other.cc"]
        with self.assertRaisesRegex(ValueError, "子集"):
            self.load()
        self.task["target_sources"] = ["a.cc"]
        self.task["allowed_test_files"] = ["project/*.cc"]
        with self.assertRaisesRegex(ValueError, "tests/"):
            self.load()


if __name__ == "__main__": unittest.main()
