#!/usr/bin/env python3
#
# Contains common generic functions.
#
# author: andreasl


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
