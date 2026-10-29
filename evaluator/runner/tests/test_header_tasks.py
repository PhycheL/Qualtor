"""跨公开 CLI 契约验证头文件题和旧题 TASK.md 的逐字节兼容。"""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT=Path(__file__).resolve().parents[3]
sys.path[:0]=[str(ROOT/'evaluator/runner'),str(ROOT/'evaluator/assessment')]
import common
from host import public_task

class PublicHeaderTest(unittest.TestCase):
    def product(self, tasks):
        code='''import json,sys
from generator.task import load_task,task_text
print(json.dumps([task_text(load_task(p)) for p in json.loads(sys.stdin.read())]))
'''
        done=subprocess.run([sys.executable,'-B','-c',code],cwd=ROOT/'agents',input=json.dumps(tasks),text=True,capture_output=True)
        self.assertEqual(done.returncode,0,done.stderr)
        return json.loads(done.stdout)

    def test_all_103_legacy_prompts_equal_baseline(self):
        golden=common.read_json(ROOT/'evaluator/assessment/tests/fixtures/step_b_legacy.json')['tasks']
        with tempfile.TemporaryDirectory() as tmp:
            paths=[]
            for task_id in golden:
                path=Path(tmp)/(task_id+'.json')
                common.write_json(path,public_task(common.load_task(task_id)))
                paths.append(str(path))
            for (task_id, expected), text in zip(golden.items(),self.product(paths)):
                with self.subTest(task=task_id):
                    self.assertEqual(hashlib.sha256(text.encode()).hexdigest(),expected['task_md'])

    def test_header_projection_loads_and_does_not_expose_hidden_materials(self):
        task=common.load_task('gildedrose-update-quality')
        task.update(target_sources=[],target_headers=['cpp/src/GildedRose.h'])
        projected=public_task(task)
        self.assertEqual(projected['target_headers'],task['target_headers'])
        self.assertNotIn('hidden',projected)
        with tempfile.TemporaryDirectory() as tmp:
            path=Path(tmp)/'task.json'
            common.write_json(path,projected)
            text=self.product([str(path)])[0]
            self.assertIn('被测头文件：project/cpp/src/GildedRose.h',text)
            self.assertIn('被测代码全部位于被测头文件中',text)
