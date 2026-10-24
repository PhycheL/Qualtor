#!/usr/bin/env python3
"""将子进程命令、返回码、时间和完整输出写入独立日志。只使用 Python 标准库。"""
import argparse
import datetime as dt
import json
import os
from pathlib import Path
import re
import signal
import subprocess
import sys
import threading
import time


def now():
    return dt.datetime.now(dt.timezone.utc).isoformat()


class Audit:
    def __init__(self, root):
        self.root = Path(root)
        self.root.mkdir(parents=True, exist_ok=True)

    def event(self, **data):
        data = {"time": now(), **data}
        with (self.root / "events.jsonl").open("a") as stream:
            stream.write(json.dumps(data, ensure_ascii=False) + "\n")
        return data

    def run(self, stage, argv, cwd=None, timeout=180, input_text=None, echo=False):
        ident = dt.datetime.now(dt.timezone.utc).strftime("%Y%m%dT%H%M%S%f")
        label = re.sub(r"[^a-zA-Z0-9_.-]", "_", stage)
        prefix = self.root / (ident + "-" + label)
        record = {"stage": stage, "argv": list(map(str, argv)), "cwd": str(cwd or Path.cwd()),
                  "started_at": now(), "timeout_seconds": timeout,
                  "stdout_log": str(prefix) + ".stdout.log", "stderr_log": str(prefix) + ".stderr.log"}
        if input_text is not None:
            record["stdin_log"] = str(prefix) + ".stdin.txt"
            Path(record["stdin_log"]).write_text(input_text)
        self.event(kind="command_start", **record)
        started = time.monotonic()
        stdout, stderr = [], []
        def drain(pipe, path, target, output):
            with open(path, "w") as log:
                for line in iter(pipe.readline, ""):
                    log.write(line)
                    log.flush()
                    target.append(line)
                    if echo:
                        output.write(line)
                        output.flush()
        env = dict(os.environ, LC_ALL="C", LANG="C", PYTHONUNBUFFERED="1")
        timed_out = False
        try:
            process = subprocess.Popen(record["argv"], cwd=cwd, env=env, stdin=subprocess.PIPE,
                                       stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True,
                                       errors="replace", start_new_session=True)
            threads = [threading.Thread(target=drain, args=(process.stdout, record["stdout_log"], stdout, sys.stdout)),
                       threading.Thread(target=drain, args=(process.stderr, record["stderr_log"], stderr, sys.stderr))]
            for thread in threads:
                thread.start()
            if input_text:
                process.stdin.write(input_text)
            process.stdin.close()
            try:
                process.wait(timeout=timeout)
            except subprocess.TimeoutExpired:
                timed_out = True
                os.killpg(process.pid, signal.SIGKILL)
                process.wait()
            for thread in threads:
                thread.join()
            returncode = process.returncode
        except OSError as error:
            returncode = 127
            stderr.append(str(error) + "\n")
            Path(record["stderr_log"]).write_text("".join(stderr))
            Path(record["stdout_log"]).touch()
        record.update(returncode=returncode, timed_out=timed_out,
                      duration_seconds=round(time.monotonic() - started, 6), ended_at=now())
        Path(str(prefix) + ".json").write_text(json.dumps(record, ensure_ascii=False, indent=2) + "\n")
        self.event(kind="command_end", **record)
        return {**record, "stdout": "".join(stdout), "stderr": "".join(stderr)}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--log-dir", type=Path, required=True)
    parser.add_argument("--stage", required=True)
    parser.add_argument("--cwd", type=Path)
    parser.add_argument("--timeout", type=int, default=1800)
    parser.add_argument("command", nargs=argparse.REMAINDER)
    args = parser.parse_args()
    command = args.command[1:] if args.command[:1] == ["--"] else args.command
    result = Audit(args.log_dir).run(args.stage, command, cwd=args.cwd, timeout=args.timeout, echo=True)
    print(json.dumps({k: result[k] for k in ["stage", "returncode", "timed_out", "duration_seconds"]}))
    sys.exit(result["returncode"] if 0 <= result["returncode"] <= 255 else 1)
