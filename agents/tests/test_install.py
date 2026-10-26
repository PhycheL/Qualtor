"""移机后失效搜索缓存必须由安装入口自动恢复；不访问网络。"""
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

AGENTS = Path(__file__).resolve().parents[1]


class SearchToolsInstallTest(unittest.TestCase):
    def test_incompatible_cached_binaries_are_replaced_and_reused(self):
        node = shutil.which("node")
        if not node:
            self.skipTest("需要宿主机 Node")
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            cache, system = root / "cache", root / "system"
            (cache / "bin").mkdir(parents=True)
            system.mkdir()
            for name in ("rg", "fd"):
                stale, replacement = cache / "bin" / name, system / name
                stale.write_text("#!/bin/sh\nexit 126\n")
                replacement.write_text(f"#!/bin/sh\necho '{name} compatible-fixture'\n")
                stale.chmod(0o755)
                replacement.chmod(0o755)
            env = dict(os.environ, PI_CODING_AGENT_DIR=str(cache), PI_OFFLINE="1",
                       PATH=str(system) + os.pathsep + os.environ["PATH"])
            command = [node, str(AGENTS / "setup_tools.mjs")]
            first = subprocess.run(command, env=env, capture_output=True, text=True, timeout=30)
            self.assertEqual(first.returncode, 0, first.stderr)
            self.assertEqual(first.stderr.count("Discarded incompatible"), 2)
            manifest = json.loads((cache / "bin/manifest.json").read_text())
            for name in ("rg", "fd"):
                self.assertEqual((cache / "bin" / name).read_bytes(), (system / name).read_bytes())
                self.assertEqual(manifest[name]["version"], name + " compatible-fixture")
            second = subprocess.run(command, env=env, capture_output=True, text=True, timeout=30)
            self.assertEqual(second.returncode, 0, second.stderr)
            self.assertNotIn("Discarded", second.stderr)
            self.assertEqual(json.loads((cache / "bin/manifest.json").read_text()), manifest)
