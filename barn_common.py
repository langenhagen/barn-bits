#!/usr/bin/env python3
#
# Contains common generic functions.
#
# author: andreasl
# version: 19-03-15

def convert_millis_to_days_hours_minutes_seconds_millis(milliseconds):
    # this is congruent with str(datetime.timedelta(milliseconds = 345649021246))
    millis = int(milliseconds % 1000)
    seconds_ = milliseconds / 1000.0
    seconds = int(seconds_ % 60)
    minutes_ = sec / 60
    minutes = int(minutes_ % 60)
    hours = int(minutes_ / 60 % 24)
    days = int(minutes_ / 60 / 24)
    return days, hours, minutes, seconds, millis

