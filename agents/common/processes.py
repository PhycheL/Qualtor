"""可取消的宿主机进程生命周期；仅使用标准库。"""
import os
import signal
import subprocess
import threading


class Cancellation(threading.Event):
    """信号处理器只置位，清理和结果落盘仍在正常控制流中完成。"""
    def __init__(self):
        super().__init__()
        self.signum = None
        self.previous = {}

    def __enter__(self):
        def cancel(signum, _frame):
            self.signum = self.signum or signum
            self.set()
        for signum in (signal.SIGINT, signal.SIGTERM):
            self.previous[signum] = signal.signal(signum, cancel)
        return self

    def __exit__(self, *_args):
        for signum, handler in self.previous.items():
            signal.signal(signum, handler)


def signal_group(process, signum):
    try:
        os.killpg(process.pid, signum)
    except (ProcessLookupError, PermissionError):
        pass


def stop_process(process, grace=5):
    if process.poll() is None:
        signal_group(process, signal.SIGTERM if grace else signal.SIGKILL)
        try:
            process.wait(timeout=grace)
        except subprocess.TimeoutExpired:
            signal_group(process, signal.SIGKILL)
            process.wait()
    # 主进程退出不代表其进程组已经退出。
    signal_group(process, signal.SIGKILL)
