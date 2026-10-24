"""分别解析 gcov 文本和 gzip JSON，核对同一源码文件的覆盖计数。"""
import gzip
import json
from pathlib import Path
import re
import shutil


def ratio(hit, total):
    return {"covered": hit, "total": total, "percent": round(100 * hit / total, 4) if total else None}


def parse_text(path):
    lines, branches = {}, []
    current_line = None
    for text in Path(path).read_text().splitlines():
        match = re.match(r"\s*([^:]+):\s*(\d+):(.*)", text)
        if match:
            count, number, content = match.groups()
            current_line = int(number)
            count = count.strip()
            if current_line and count != "-":
                lines[current_line] = 0 if count in ("#####", "=====") else int(count.replace("*", ""))
        branch = re.match(r"branch\s+(\d+)\s+(?:taken\s+(\d+)|(never executed))(.*)", text.strip())
        if branch:
            ident, count, never, flags = branch.groups()
            branches.append({"line": current_line, "id": int(ident), "count": int(count or 0), "throw": "throw" in flags})
    normal = [b for b in branches if not b["throw"]]
    return {"line": ratio(sum(v > 0 for v in lines.values()), len(lines)),
            "branch_all": ratio(sum(b["count"] > 0 for b in branches), len(branches)),
            "branch_nonthrow": ratio(sum(b["count"] > 0 for b in normal), len(normal)),
            "uncovered_lines": [k for k, v in lines.items() if not v],
            "uncovered_branches": [b for b in branches if not b["count"]]}


def parse_json(path, source_name="GildedRose.cc"):
    with gzip.open(path, "rt") as stream:
        document = json.load(stream)
    files = [f for f in document["files"] if Path(f["file"]).name == source_name]
    if len(files) != 1:
        raise ValueError(f"expected one {source_name}, found {len(files)}")
    source = files[0]
    lines = source["lines"]
    branches = [b for line in lines for b in line.get("branches", [])]
    normal = [b for b in branches if not b.get("throw", False)]
    return {"source": source["file"], "format_version": document["format_version"],
            "gcc_version": document.get("gcc_version"),
            "line": ratio(sum(l["count"] > 0 for l in lines), len(lines)),
            "branch_all": ratio(sum(b["count"] > 0 for b in branches), len(branches)),
            "branch_nonthrow": ratio(sum(b["count"] > 0 for b in normal), len(normal))}


def collect(build, output, audit, source_name="GildedRose.cc"):
    candidates = list(Path(build).rglob(source_name + ".gcda"))
    if len(candidates) != 1:
        raise ValueError(f"expected exactly one gcda, got {candidates}")
    data = candidates[0]
    raw_dir = Path(output) / "raw"
    raw_dir.mkdir(parents=True)
    shutil.copy2(data, raw_dir / data.name)
    shutil.copy2(data.with_suffix(".gcno"), raw_dir / data.with_suffix(".gcno").name)
    data = raw_dir / data.name
    text_dir, json_dir = Path(output) / "text", Path(output) / "json"
    text_dir.mkdir(parents=True)
    json_dir.mkdir(parents=True)
    text_run = audit.run("gcov-text", ["gcov", "-b", "-c", str(data)], cwd=text_dir)
    json_run = audit.run("gcov-json", ["gcov", "-b", "-c", "-j", str(data)], cwd=json_dir)
    if text_run["returncode"] or json_run["returncode"]:
        raise RuntimeError("gcov failed; see logs")
    text_files = list(text_dir.glob(source_name + ".gcov"))
    json_files = list(json_dir.glob("*.gcov.json.gz"))
    if len(text_files) != 1 or len(json_files) != 1:
        raise ValueError("unexpected gcov output layout")
    text_stats = parse_text(text_files[0])
    json_stats = parse_json(json_files[0], source_name)
    agreement = all(text_stats[k] == json_stats[k] for k in ["line", "branch_all", "branch_nonthrow"])
    result = {"text": text_stats, "json": json_stats, "parsers_agree": agreement,
              "gcda": str(data), "text_file": str(text_files[0]), "json_file": str(json_files[0])}
    (Path(output) / "coverage.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n")
    if not agreement:
        raise AssertionError("gcov text and JSON coverage disagree")
    return result


# ---- 评分器使用：多个被测源文件、函数覆盖、GCOV_PREFIX 重定向的 .gcda ----

def text_source(path):
    """读取 .gcov 文本头部的 Source: 行，得到它对应的源文件路径。"""
    with open(path, errors="replace") as stream:
        for _ in range(5):
            match = re.match(r"\s*-:\s*0:Source:(.*)$", stream.readline())
            if match:
                return match.group(1).strip()
    return None


def parse_json_sources(path, sources):
    """gcov JSON -> {源文件: 行、分支、函数计数}，只保留指定的被测源文件。"""
    with gzip.open(path, "rt") as stream:
        document = json.load(stream)
    found = {}
    for entry in document["files"]:
        if entry["file"] not in sources:
            continue
        lines = entry["lines"]
        branches = [b for line in lines for b in line.get("branches", [])]
        normal = [b for b in branches if not b.get("throw", False)]
        functions = entry.get("functions", [])
        found[entry["file"]] = {
            "line": ratio(sum(l["count"] > 0 for l in lines), len(lines)),
            "branch_all": ratio(sum(b["count"] > 0 for b in branches), len(branches)),
            "branch_nonthrow": ratio(sum(b["count"] > 0 for b in normal), len(normal)),
            "function": ratio(sum(f.get("execution_count", 0) > 0 for f in functions), len(functions)),
            "uncovered_functions": sorted(f.get("demangled_name", f.get("name")) for f in functions
                                          if not f.get("execution_count")),
            "format_version": document.get("format_version"), "gcc_version": document.get("gcc_version")}
    return found


def collect_targets(prefix_dir, sources, output, audit, gcov="gcov"):
    """采集 GCOV_PREFIX 下的 .gcda（GCOV_PREFIX_STRIP=0），对被测源文件分别用文本和 JSON 两种输出核对。

    .gcno 位于 .gcda 去掉前缀后的原始绝对路径；先复制到 .gcda 旁边，再在独立目录中运行 gcov。
    """
    prefix_dir, output = Path(prefix_dir), Path(output)
    sources = set(sources)
    per_file, text_stats = {}, {}
    gcdas = sorted(prefix_dir.rglob("*.gcda"))
    for index, data in enumerate(gcdas):
        notes = Path("/" + str(data.relative_to(prefix_dir))).with_suffix(".gcno")
        if not notes.is_file():
            raise FileNotFoundError(f"missing gcno for {data}: {notes}")
        shutil.copy2(notes, data.with_suffix(".gcno"))
        text_dir, json_dir = output / f"text-{index:02d}", output / f"json-{index:02d}"
        text_dir.mkdir(parents=True)
        json_dir.mkdir(parents=True)
        text_run = audit.run(f"gcov-text-{index:02d}", [gcov, "-b", "-c", "-p", str(data)], cwd=text_dir)
        json_run = audit.run(f"gcov-json-{index:02d}", [gcov, "-b", "-c", "-j", "-p", str(data)], cwd=json_dir)
        if text_run["returncode"] or json_run["returncode"]:
            raise RuntimeError("gcov failed; see logs")
        for report in sorted(json_dir.glob("*.gcov.json.gz")):
            for source, stats in parse_json_sources(report, sources).items():
                if source in per_file:
                    raise ValueError(f"{source} appears in more than one gcov data file")
                per_file[source] = stats
        for report in sorted(text_dir.glob("*.gcov")):
            source = text_source(report)
            if source in sources:
                text_stats[source] = parse_text(report)
    missing = sorted(sources - set(per_file))
    agree = all(source in text_stats and all(text_stats[source][k] == per_file[source][k]
                                             for k in ("line", "branch_all", "branch_nonthrow"))
                for source in per_file)
    total = {key: {"covered": sum(per_file[s][field]["covered"] for s in per_file),
                   "total": sum(per_file[s][field]["total"] for s in per_file)}
             for key, field in (("lines", "line"), ("branches", "branch_all"), ("functions", "function"))}
    result = {"files": per_file, "total": total, "missing_sources": missing, "parsers_agree": agree,
              "text_uncovered_lines": {s: text_stats[s]["uncovered_lines"] for s in text_stats}}
    (output / "coverage.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n")
    return result
