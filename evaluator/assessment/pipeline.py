"""宿主机侧测试评测流程：对一份冻结产物依次执行步骤 1–8，写出 result.json。

步骤与判定见 docs/评测模块与校准样本设计.md 第 5 节、docs/评分算法.md 第 3–4 节。
"""
from pathlib import Path
import shutil
import traceback

from common import (REPO, ASSESSMENT, copy_variant_tree, load_baseline, load_coverage_baseline,
                    mutation_not_applicable, mull_config_text, now, product_test_sources, read_json,
                    assessment_code_sha256, assessment_version, sha256_file, sha256_text, source_root, task_sha256,
                    validate_product, variant_dir, write_json)
import judge

TIMEOUT = {"build": 900, "run": 1800, "mull": 3600}


class Infra(Exception):
    """评测模块、工具链或题目材料的问题：这次评分记为基础设施错误，修复后重评。"""


def _rel(path, base):
    try:
        return str(Path(path).relative_to(base))
    except ValueError:
        return str(path)


class ProductAssessment:
    def __init__(self, executor, task, product, out_dir, meta, audit, cost_path=None, prep=False,
                 calibration=None):
        self.ex, self.task, self.audit, self.prep = executor, task, audit, prep
        self.product = Path(product).resolve()
        self.out = Path(out_dir).resolve()
        self.cost_path = Path(cost_path) if cost_path else None
        self.root = source_root(task)
        self.params = task["params"]
        manifest = self.product / "manifest.json"
        self.result = {
            "schema": 1,
            # schema 1 保留旧字段名；历史结果与补评、汇总共用同一契约。
            "scorer": {"version": assessment_version(), "code_sha256": assessment_code_sha256(),
                       "calibration": calibration or {"status": "not_checked"}},
            # sha256 是题目全部隐藏材料与分母的指纹，汇总时据此核对题目是否已准入（R-08）。
            "task": {"id": task["id"], "set": task["set"], "task_json_sha256": task["_sha256"],
                     "sha256": task_sha256(task)},
            "product": {"path": _rel(self.product, REPO),
                        "manifest_sha256": sha256_file(manifest) if manifest.is_file() else None},
            "meta": meta, "mode": "prep" if prep else "score", "executor": executor.mode,
            "images": executor.images, "started_at": now(),
            "status": None, "invalid_reason": None, "infra_detail": None,
            "build": None, "tests": {}, "counts": {}, "mutants": None, "variants": [], "cost": None,
            "steps": {}, "warnings": []}

    # ---- 路径 ----

    def at(self, name, host=None):
        return self.ex.at(name, host)

    def repo_path(self, rel, root=None):
        return f"{self.at('repo', root or self.root)}/{rel}"

    def target_paths(self, root=None):
        return [self.repo_path(rel, root) for rel in self.task["target_sources"]]

    def build_job(self, mode, build_mount, target_sources, root=None):
        product = self.at("product", self.product)
        return {"phase": "build", "mode": mode, "template_dir": f"{self.at('assessment', ASSESSMENT)}/cmake",
                "build_dir": build_mount, "target_sources": target_sources,
                **({"target_headers": [self.repo_path(rel, root) for rel in self.task["target_headers"]]}
                   if self.task.get("target_headers") else {}),
                "support_sources": [self.repo_path(rel, root) for rel in self.task.get("build", {}).get("support_sources", [])],
                "build": self.task.get("build", {}),
                "include_dirs": [self.repo_path(rel, root) for rel in self.task["include_dirs"]] + [f"{product}/tests"],
                "test_sources": [f"{product}/{rel}" for rel in product_test_sources(self.product)],
                "test_files": [f"{product}/{p.relative_to(self.product)}"
                               for p in sorted((self.product / "tests").rglob("*")) if p.is_file()],
                "timeout": TIMEOUT["build"]}

    def phase(self, label, toolchain, mounts, job, env=None, kind="build"):
        out_host = self.out / label
        out_mount = self.at("out", out_host)
        job["out_dir"], job["work_dir"] = out_mount, f"{out_mount}/work"
        job.update(self.ex.tools(toolchain))
        step = self.ex.run_phase(label, toolchain, mounts, env or {}, job, out_host, TIMEOUT[kind], self.audit)
        self.result["steps"][label] = {"status": step.get("status"), "reason": step.get("reason"),
                                       "dir": _rel(out_host, REPO)}
        if step.get("status") == "infra_error":
            raise Infra(f"{label}: {step.get('reason')}")
        return step

    # ---- 主流程 ----

    def run(self):
        self.out.mkdir(parents=True, exist_ok=False)
        try:
            self._assess()
        except Infra as error:
            self._finish(judge.INFRA_ERROR, None, infra=str(error))
        except Exception:
            self._finish(judge.INFRA_ERROR, None, infra="pipeline_exception: " + traceback.format_exc()[-2000:])
        self.result["metrics"] = judge.metrics(self.result) if self.result["status"] != judge.INFRA_ERROR else None
        self.result["finished_at"] = now()
        write_json(self.out / "result.json", self.result)
        return self.result

    def _finish(self, status, reason, infra=None):
        self.result["status"], self.result["invalid_reason"], self.result["infra_detail"] = status, reason, infra

    def _assess(self):
        na = mutation_not_applicable(self.task, {} if self.prep else None)
        if na:
            self.result["not_applicable"] = {"M1": na}
        if self.task.get("target_headers"):
            self.result.setdefault("not_applicable", {})["C2"] = "header_only"
        # 成本来自生成过程，即使产物无效也必须保留，不能被后面的提前返回跳过。
        if self.cost_path and self.cost_path.is_file():
            self.result["cost"] = read_json(self.cost_path)
        else:
            self.result["warnings"].append("cost_missing")
        problem = validate_product(self.product, self.task)
        if problem:
            self.result["product"]["problem"] = problem
            return self._finish(judge.INVALID, "artifact_rejected")
        coverage = self.ex.capabilities["coverage"]
        # 步骤 1：GCC 构建
        gcc_build = self.out / "gcc-build" / "build"
        gcc_build.mkdir(parents=True)
        step = self.phase("gcc-build", "gcc",
                          {"repo": (self.root, True), "product": (self.product, True), "build": (gcc_build, False)},
                          self.build_job("coverage" if coverage else "plain", self.at("build", gcc_build),
                                         self.target_paths()))
        self.result["build"] = {k: step.get(k) for k in ("status", "reason", "diagnostics")}
        if step["status"] != "built":
            return self._finish(*judge.artifact_status(build=self.result["build"]))
        # 步骤 2–5：发现、运行、稳定性、覆盖率
        job = {"phase": "run", "mode": "full", "binary": f"{self.at('build', gcc_build)}/scored_tests",
               "test_timeout": self.params["test_timeout_seconds"], "repeats": self.params["stability_repeats"],
               "shuffle_seeds": self.params["shuffle_seeds"],
               "coverage": ({"prefix_dir": f"{self.at('out', self.out / 'gcc-run')}/gcov-final",
                             "sources": ([self.repo_path(p) for p in self.task["target_headers"]]
                                         if self.task.get("target_headers") else self.target_paths()),
                             **({"headers": True} if self.task.get("target_headers") else {}),
                             "gcov": "gcov-14"} if coverage else None)}
        step = self.phase("gcc-run", "gcc", {"repo": (self.root, True), "build": (gcc_build, True)}, job, kind="run")
        record = step["record"]
        self._check_record(record)
        status, reason = judge.artifact_status(build=self.result["build"], record=record)
        self.result["tests"] = record.get("final_statuses") or {}
        self.result["counts"]["tests"] = judge.test_counts(record, self.params["stability_repeats"])
        self.result["counts"]["coverage"] = self._coverage(record.get("coverage"))
        if status != judge.SCORED:
            return self._finish(status, reason)
        valid = judge.valid_tests(record)
        # 步骤 6：变异测试
        if na:
            pass
        elif self.ex.capabilities["mull"]:
            self._mull(valid)
        else:
            self.result["warnings"].append("mull_skipped: executor 不支持 Mull（仅限宿主机辅助检查）")
        # 步骤 7：替换版本
        for index, variant in enumerate(sorted(self.task["variants"], key=lambda v: v["id"]), 1):
            self.result["variants"].append(self._variant(index, variant, valid))
        self._finish(judge.SCORED, None)

    def _check_record(self, record):
        """宿主机按原始记录重新判定一次，与容器内的判定不一致即视为评测模块故障。"""
        discovery = record.get("discovery") or {}
        if not discovery.get("ok") or not discovery.get("tests"):
            return
        step3, problem = judge.step3_statuses(discovery["tests"], record.get("full_run"), record.get("isolation"))
        final = judge.final_test_statuses(step3, record.get("stability") or {}) if not problem else step3
        if step3 != record.get("step3") or problem != record.get("step3_problem") or final != record.get("final_statuses"):
            raise Infra("judge_mismatch: 宿主机与容器内的测试状态判定不一致")

    def _coverage(self, coverage):
        if not coverage:
            return None
        if coverage.get("status") != "ok":
            self.result["warnings"].append(f"coverage_unavailable: {coverage.get('reason')}")
            return None
        data = coverage["data"]
        if self.task.get("target_headers"):
            from coverage import frozen_header_coverage
            files = {_rel(path, self.repo_path("")): stats for path, stats in data["files"].items()}
            if self.prep:
                return {"files": files, "total": data["total"]}
            baseline = load_coverage_baseline(self.task)
            if not baseline or set(baseline.get("headers", {})) != set(self.task["target_headers"]):
                raise Infra("missing_or_mismatched_coverage_baseline")
            for rel, frozen in baseline["headers"].items():
                if frozen["sha256"] != self.task["source"]["files"][rel] or not frozen["lines"]:
                    raise Infra(f"coverage_baseline_source_changed: {rel}")
            return frozen_header_coverage(files, baseline)
        files = {}
        for path, stats in data["files"].items():
            files[_rel(path, self.repo_path(""))] = {"lines": stats["line"], "branches": stats["branch_all"],
                                                       "functions": stats["function"],
                                                       "uncovered_functions": stats["uncovered_functions"],
                                                       "no_executable_code": stats.get("no_executable_code", False)}
        return {"files": files, "total": data["total"]}

    def _mull(self, valid):
        config_dir = self.out / "clang-build" / "config"
        config_dir.mkdir(parents=True)
        text = mull_config_text(self.task, container_root=self.at("repo", self.root))
        (config_dir / "mull.yml").write_text(text)
        config_sha = sha256_text(text)
        env = {"MULL_CONFIG": f"{self.at('config', config_dir)}/mull.yml"}
        clang_build = self.out / "clang-build" / "build"
        clang_build.mkdir(parents=True)
        step = self.phase("clang-build", "clang",
                          {"repo": (self.root, True), "product": (self.product, True), "config": (config_dir, True),
                           "build": (clang_build, False)},
                          self.build_job("mull", self.at("build", clang_build), self.target_paths()), env)
        if step["status"] != "built":
            if not self.prep and step.get("failure_origin") == "product_tests":
                self.result["metric_failures"] = {"M1": {
                    "reason": "clang_test_compile_failed", "errors": step["errors"],
                    "evidence_dir": self.result["steps"]["clang-build"]["dir"]}}
                return
            raise Infra(f"clang_build_failed: {step.get('reason')}; {step.get('diagnostics')}")
        job = {"phase": "mull", "binary": f"{self.at('build', clang_build)}/scored_tests", "tests": valid,
               "sources": self.target_paths(), "workers": 2,
               "allow_zero_mutants": self.prep,
               "minimum_timeout_ms": self.params["mull_minimum_timeout_ms"], "timeout": TIMEOUT["mull"]}
        step = self.phase("mull", "clang", {"repo": (self.root, True), "build": (clang_build, True),
                                            "config": (config_dir, True)}, job, env, kind="mull")
        mutants = step["mutants"]
        self.result["mull_config_sha256"] = config_sha
        if self.prep and step.get("not_applicable") == "zero_mutants":
            self.result["not_applicable"] = {"M1": "zero_mutants"}
            self.result["zero_mutants_evidence"] = step["zero_mutants_evidence"]
        if self.prep:
            self.result["raw_mutants"] = [{k: m[k] for k in ("id", "mutator", "status", "location")} for m in mutants]
            counts = {}
            for m in mutants:
                status = judge.mull_status(m["status"])
                counts[status] = counts.get(status, 0) + 1
            self.result["counts"]["mutants"] = {"raw": dict(sorted(counts.items())), "total_raw": len(mutants)}
            return
        baseline = load_baseline(self.task)
        problem, counts, per_mutant = judge.evaluate_mutants(mutants, baseline, config_sha)
        if problem:
            raise Infra(problem)
        review = baseline.get("review", {}).get("status")
        if review != "reviewed":
            self.result["warnings"].append(f"mutation_baseline_review: {review}")
        self.result["counts"]["mutants"] = counts
        self.result["mutants"] = per_mutant

    def _variant(self, index, variant, valid):
        label = f"v{index:02d}"
        build_dir = self.out / f"{label}-build" / "build"
        build_dir.mkdir(parents=True)
        vdir = self.out / f"{label}-source"
        if vdir.exists() or vdir.is_symlink():
            raise Infra(f"variant_source_already_exists: {vdir}")
        try:
            tree_sha256 = copy_variant_tree(self.task, variant, vdir)
            self.result["steps"][f"{label}-source"] = {"status": "copied", "source_tree_sha256": tree_sha256}
            return self._variant_from_tree(label, variant, valid, vdir, build_dir, tree_sha256)
        finally:
            if vdir.exists():
                shutil.rmtree(vdir)

    def _variant_from_tree(self, label, variant, valid, vdir, build_dir, tree_sha256):
        targets = self.target_paths(vdir)
        step = self.phase(f"{label}-build", "gcc",
                          {"repo": (vdir, True), "product": (self.product, True),
                           "build": (build_dir, False)},
                          self.build_job("plain", self.at("build", build_dir), targets, root=vdir))
        outcomes = {}
        if step["status"] == "built":
            job = {"phase": "run", "mode": "variant", "binary": f"{self.at('build', build_dir)}/scored_tests",
                   "tests": valid, "test_timeout": self.params["test_timeout_seconds"],
                   "repeats": 0, "shuffle_seeds": []}
            run = self.phase(f"{label}-run", "gcc", {"build": (build_dir, True)}, job, kind="run")
            outcomes = run["record"]["variant_outcomes"]
        outcome, failed, problem = judge.variant_outcome(variant, step["status"] == "built", outcomes, valid)
        if problem:
            raise Infra(problem)
        return {"id": variant["id"], "kind": variant["kind"], "expect": variant["expect"], "outcome": outcome,
                "failed_tests": failed, "label": label, "source_tree_sha256": tree_sha256}


def assess_product(executor, task, product, out_dir, meta, audit, cost_path=None, prep=False, calibration=None):
    return ProductAssessment(executor, task, product, out_dir, meta, audit, cost_path, prep, calibration).run()
