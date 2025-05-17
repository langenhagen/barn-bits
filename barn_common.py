#!/usr/bin/env python3
"""Contains common generic functions.

author: andreasl
"""


def convert_millis_to_days_hours_minutes_seconds_millis(
    milliseconds: int,
) -> tuple[int, int, int, int, int]:
    """Get a tuple of (days, hours, minutes, seconds, millis) from a given
    number of milliseconds."""
    # this is congruent with str(datetime.timedelta(milliseconds = 345649021246))
    millis = int(milliseconds % 1000)
    seconds_ = int(milliseconds / 1000)
    seconds = seconds_ % 60
    minutes_ = seconds_ // 60
    minutes = minutes_ % 60
    hours_ = minutes_ // 60
    hours = hours_ % 24
    days = hours_ // 24
    return days, hours, minutes, seconds, millis


import json
import requests
def get_request_as_string(request: requests.PreparedRequest):
    """Get a string representation of a requests.PreparedRequest object."""
    headers = json.dumps({k: v for k, v in request.headers.items()}, indent=True)
    return (
        f"{request.method} {request.url}\n"
        f"Headers:\n{headers}\n"
        f"Body:\n{request.body}\n"
    )


import sys
import termios
import tty
def getch() -> str:
    """Get a single pressed character from keyboard without ENTER in a blocking
    fashion."""
    file_descriptor = sys.stdin.fileno()
    old_settings = termios.tcgetattr(file_descriptor)
    try:
        tty.setraw(sys.stdin.fileno())
        char = sys.stdin.read(1)
    finally:
        termios.tcsetattr(file_descriptor, termios.TCSADRAIN, old_settings)
    return char


import re
import subprocess
def get_processor_name() -> str:
    """Return the processor name on a Linux machine."""
    cmd = "cat /proc/cpuinfo"
    all_info = subprocess.check_output(cmd, shell=True).decode().strip()
    for line in all_info.split("\n"):
        if "model name" in line:
            return re.sub(r".*model name.*:\s*", "", line, 1)

    return ""


from pathlib import Path
def get_free_memory_mb_via_cgroups() -> float:
    """Get remaining memory as derived from the values in the cgroups files;
    applicable for instances running in Kubernetes. In order for this to work,
    the memory cgroup subsystem has to be enabled. This is usually the case in
    Kubernetes-hosted instances, but not necessarily on your laptop.

    Caution: Note that the cgroups available memory may not reflect the actual
    state of the node's available memory.

    Returns:
        float: the remaining available memory in megabytes.
    """

    mem_limit_path = Path("/sys/fs/cgroup/memory/memory.limit_in_bytes")
    mem_usage_path = Path("/sys/fs/cgroup/memory/memory.usage_in_bytes")

    mem_limit_bytes = int(mem_limit_path.read_text().strip())
    mem_usage_bytes = int(mem_usage_path.read_text().strip())

    return (mem_limit_bytes - mem_usage_bytes) / (1024 * 1024)


def get_free_memory_mb_via_proc_meminfo() -> float:
    """Get remaining memory via `/proc/meminfo`; applicable for your laptop, but
    not applicable for instances running in Kubernetes since `/proc/meminfo`
    shows host memory, not cgroup limits, so it ignores Kubernetes container
    restrictions.

    Returns:
        float: the remaining available memory in megabytes.
    """
    with open("/proc/meminfo") as f:
        meminfo = {line.split(":")[0]: int(line.split()[1]) for line in f}
    return meminfo["MemAvailable"] / 1024


def get_free_memory_mb() -> float:
    """Get remaining memory, depending on whether according cgroups memory
    subsystem files are there, either via cgroups, or otherwise via psutil.
    This usually works on both kubernetes instances and local machines.

    Returns:
        float: the remaining available memory in megabytes."""

    mem_cgroup_path = Path("/sys/fs/cgroup/memory")
    if mem_cgroup_path.is_dir():
        return get_free_memory_mb_via_cgroups()
    return get_free_memory_mb_via_proc_meminfo()
