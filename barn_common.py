#!/usr/bin/env python3
#
# Contains common generic functions.
#
# author: andreasl
# version: 19-06-24


def convert_millis_to_days_hours_minutes_seconds_millis(milliseconds: int):
    """Get a tuple of (days, hours, minutes, seconds, millis) from a given number of milliseconds."""
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
