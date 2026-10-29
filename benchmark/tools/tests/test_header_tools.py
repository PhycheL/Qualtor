import difflib
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import bankutil


class HeaderToolsTest(unittest.TestCase):
    def test_rebuild_preserves_both_baselines_only_when_material_is_identical(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(bankutil, 'BENCHMARK', Path(tmp)):
            task = bankutil.reset_task_dir('header', False)
            bankutil.write_text(task / 'source/a.h', 'inline int f(){return 1;}\n')
            for name in bankutil.BASELINES:
                bankutil.write_text(task / 'hidden' / name, name)
            bankutil.reset_task_dir('header', True)
            bankutil.write_text(task / 'source/a.h', 'inline int f(){return 1;}\n')
            (task / 'hidden').mkdir()
            bankutil.restore_baseline(task, 'header')
            for name in bankutil.BASELINES:
                self.assertEqual((task / 'hidden' / name).read_text(), name)
            bankutil.reset_task_dir('header', True)
            bankutil.write_text(task / 'source/a.h', 'inline int f(){return 2;}\n')
            bankutil.restore_baseline(task, 'header')
            self.assertFalse(any((task / 'hidden' / n).exists() for n in bankutil.BASELINES))

    def test_header_patch_is_reproducible_and_does_not_change_source(self):
        with tempfile.TemporaryDirectory() as tmp:
            task = Path(tmp)
            original = 'inline int f(){return 1;}\n'
            replacement = 'inline int f(){return 2;}\n'
            bankutil.write_text(task / 'source/src/a.h', original)
            diff = ''.join(difflib.unified_diff(original.splitlines(True), replacement.splitlines(True),
                                               fromfile='a/src/a.h', tofile='b/src/a.h'))
            bankutil.write_text(task / 'change.patch', diff)
            first = bankutil.apply_patch_variant(task, task / 'change.patch', 'hw-01', 'handwritten', '错误常量')
            second = bankutil.apply_patch_variant(task, task / 'change.patch', 'hw-01', 'handwritten', '错误常量')
            self.assertEqual(first, second)
            self.assertEqual((task / 'source/src/a.h').read_text(), original)
            self.assertEqual((task / 'hidden/variants/hw-01/src/a.h').read_text(), replacement)
            bankutil.write_text(task / 'change.patch', diff.replace('src/a.h', '../a.h'))
            with self.assertRaises(ValueError):
                bankutil.apply_patch_variant(task, task / 'change.patch', 'bad', 'handwritten', '')
