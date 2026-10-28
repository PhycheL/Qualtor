import unittest

from support import scored_result
import aggregate


def runs(agent, values_by_task, **kwargs):
    return [scored_result(task=task, agent=agent, trial=k + 1, m1=value, **kwargs)
            for task, values in values_by_task.items() for k, value in enumerate(values)]


class SummarizeTest(unittest.TestCase):
    def test_task_means_skip_not_applicable_and_infra(self):
        results = runs("A", {"t1": [0.4, 0.6]}) + [scored_result(task="t1", agent="A", trial=3, status="infra_error")]
        results.append(scored_result(task="t1", agent="A", trial=4, status="invalid", m1=None))
        summary = aggregate.summarize(results, "dev", "final")["A"]
        task = summary["tasks"]["t1"]
        self.assertEqual(task["infra_missing"], 1)
        self.assertAlmostEqual(task["M1_e2e"], (0.4 + 0.6 + 0.0) / 3)   # 无效产物端到端记 0
        self.assertAlmostEqual(task["M1_valid"], 0.5)                   # 仅有效：跳过不适用
        self.assertEqual(task["K1.seconds"]["median"], 10)

    def test_tasks_weighted_equally(self):
        results = runs("A", {"t1": [1.0, 1.0, 1.0, 1.0], "t2": [0.0]})
        overall = aggregate.summarize(results, "dev", "final")["A"]["overall"]["M1_e2e"]
        self.assertAlmostEqual(overall["mean"], 0.5)
        self.assertEqual(overall["tasks"], 2)

    def test_duplicates_rejected(self):
        with self.assertRaises(SystemExit):
            aggregate.index(runs("A", {"t1": [0.5]}) + runs("A", {"t1": [0.5]}))


class CompareTest(unittest.TestCase):
    tasks = {f"t{i}": [0.5 + 0.01 * i, 0.52 + 0.01 * i, 0.48 + 0.01 * i] for i in range(12)}

    def shifted(self, delta):
        return {t: [v + delta for v in values] for t, values in self.tasks.items()}

    def test_identical_versions_are_indistinguishable(self):
        result = aggregate.compare(runs("A", self.tasks) + runs("B", self.tasks), "A", "B", 0.05, {}, replicates=2000)
        self.assertAlmostEqual(result["delta"], 0.0)
        self.assertEqual(result["decision"], "无法区分")

    def test_clear_improvement_is_better(self):
        result = aggregate.compare(runs("A", self.tasks) + runs("B", self.shifted(0.1)), "A", "B", 0.05,
                                   {"V2": 0.05}, replicates=2000)
        self.assertAlmostEqual(result["delta"], 0.1)
        self.assertGreater(result["ci"][0], 0)
        self.assertEqual(result["decision"], "更好")
        self.assertIsNone(result["note"])

    def test_guard_failure_is_improvement_with_cost(self):
        results = runs("A", self.tasks, seconds=10) + runs("B", self.shifted(0.1), seconds=100)
        result = aggregate.compare(results, "A", "B", 0.05, {"K1.seconds": 30}, replicates=2000)
        self.assertEqual(result["decision"], "主指标提升但有代价：K1.seconds")
        self.assertEqual(result["guards"]["K1.seconds"]["worse"], 90)

    def test_regression_is_worse(self):
        result = aggregate.compare(runs("A", self.tasks) + runs("B", self.shifted(-0.1)), "A", "B", 0.05, {},
                                   replicates=2000)
        self.assertEqual(result["decision"], "更差")

    def test_bootstrap_is_reproducible_and_flags_few_tasks(self):
        few = {"t1": [0.5, 0.6], "t2": [0.4, 0.5]}
        a = aggregate.compare(runs("A", few) + runs("B", few), "A", "B", 0.05, {}, replicates=500, seed=7)
        b = aggregate.compare(runs("A", few) + runs("B", few), "A", "B", 0.05, {}, replicates=500, seed=7)
        self.assertEqual(a["ci"], b["ci"])
        self.assertEqual(a["note"], "题数不足 10，结论仅供参考")

    def test_only_paired_tasks_are_compared(self):
        results = runs("A", {"t1": [0.5], "t2": [0.5]}) + runs("B", {"t1": [0.6]})
        result = aggregate.compare(results, "A", "B", 0.05, {}, replicates=200)
        self.assertEqual(result["tasks"], ["t1"])

    def test_calibration_problems(self):
        results = runs("A", {"t1": [0.5]}, calibrated=False)
        self.assertTrue(aggregate.calibration_problems(results))
        self.assertFalse(aggregate.calibration_problems(runs("A", {"t1": [0.5]})))

    def test_admission_problems(self):
        results = runs("A", {"t1": [0.5], "t2": [0.5], "t3": [0.5]})
        for result, sha in zip(results, ("h1", "old", None)):
            result["task"]["sha256"] = sha
        admitted = {"t1": {"task_sha256": "h1"}, "t2": {"task_sha256": "h2"}}
        problems = aggregate.admission_problems(results, admitted)
        # t1 指纹一致；t2 准入后材料变化；t3 未准入
        self.assertEqual(problems, ["未准入的题目：t3", "准入后材料已变化或结果未记录题目指纹的题目：t2"])
        self.assertEqual(aggregate.admission_problems(results[:1], admitted), [])
        # 旧结果没有记录题目指纹，即使题目已准入也不能直接用于正式比较
        legacy = runs("A", {"t1": [0.5]})
        self.assertEqual(len(aggregate.admission_problems(legacy, admitted)), 1)


if __name__ == "__main__":
    unittest.main()
