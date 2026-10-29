from pathlib import Path
import json
import sys
import tempfile
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from generator.task import load_task

class HeaderTaskTest(unittest.TestCase):
    def test_header_only_accepted_mixed_and_bad_suffix_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp)
            for rel in ('a.h','a.cc','dep.cc'): (root/rel).write_text('')
            task={'id':'header','title':'header','source_root':str(root),'target_sources':[],
                  'target_headers':['a.h'],'visible_files':['a.h','a.cc','dep.cc'],'include_dirs':['.'],
                  'allowed_test_files':['tests/*.cc'],'budget':{'repair_rounds':3},'test_timeout_seconds':5,
                  'build':{'support_sources':['dep.cc']}}
            path=root/'task.json'
            path.write_text(json.dumps(task))
            self.assertEqual(load_task(path)['target_sources'],[])
            for targets,headers in [(['a.cc'],['a.h']),([],['a.cc']),([],[])]:
                path.write_text(json.dumps({**task,'target_sources':targets,'target_headers':headers}))
                with self.assertRaises(ValueError):load_task(path)
