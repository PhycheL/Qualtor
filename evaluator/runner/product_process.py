"""评测对公开产品 CLI 的进程适配：记录命令，并转发用户取消。"""
import os
from pathlib import Path
import signal
import subprocess
import threading
import time
import uuid

from audit import now
from common import write_json


class Cancellation(threading.Event):
    def __enter__(self):
        self.signum = None
        self.previous = {}
        def cancel(signum, _frame):
            self.signum = self.signum or signum
            self.set()
        for signum in (signal.SIGINT, signal.SIGTERM):
            self.previous[signum] = signal.signal(signum, cancel)
        return self

    def __exit__(self, *_args):
        for signum, handler in self.previous.items():
            signal.signal(signum, handler)


def stop(process):
    if process.poll() is None:
        try:
            os.killpg(process.pid, signal.SIGTERM)
        except ProcessLookupError:
            pass
        try:
            process.wait(timeout=70)
        except subprocess.TimeoutExpired:
            os.killpg(process.pid, signal.SIGKILL)
            process.wait()
    try:
        os.killpg(process.pid, signal.SIGKILL)
    except ProcessLookupError:
        pass


def run_product(audit, command, cancel=None):
    prefix = audit.root / ("generate-product-" + uuid.uuid4().hex)
    record = {"stage": "generate-product", "argv": list(map(str, command)), "cwd": str(Path.cwd()),
              "started_at": now(), "timeout_seconds": None,
              "stdout_log": str(prefix) + ".stdout.log", "stderr_log": str(prefix) + ".stderr.log"}
    audit.event(kind="command_start", **record)
    started, process, interrupted = time.monotonic(), None, None
    cancelled, returncode = False, 127
    try:
        with open(record["stdout_log"], "w") as stdout, open(record["stderr_log"], "w") as stderr:
            if cancel is None or not cancel.is_set():
                process = subprocess.Popen(command, stdin=subprocess.DEVNULL, stdout=stdout, stderr=stderr,
                                           start_new_session=True)
                while process.poll() is None:
                    if cancel is not None and cancel.is_set():
                        cancelled = True
                        break
                    try:
                        process.wait(timeout=0.1)
                    except subprocess.TimeoutExpired:
                        pass
            else:
                cancelled = True
    except BaseException as error:
        interrupted, cancelled = error, True
    finally:
        if process is not None:
            stop(process)
            returncode = process.returncode
        record.update(returncode=returncode, cancelled=cancelled, timed_out=False, output_incomplete=False,
                      duration_seconds=round(time.monotonic() - started, 6), ended_at=now())
        write_json(str(prefix) + ".json", record)
        audit.event(kind="command_end", **record)
    if interrupted is not None:
        raise interrupted
    return record
