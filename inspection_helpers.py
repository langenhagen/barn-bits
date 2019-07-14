"""Contains helper functions that aid working with Python's inspection features."""
import inspect
import sys


def get_function_name():
    """Retrieve the calling function name."""
    frame = sys._getframe(1)
    function_name = frame.f_code.co_name
    return function_name


def get_function_arguments():
    """Retrieve the calling function's parameter/argument dictionary."""
    frame = sys._getframe(1)
    _, _, _, param_names_values = inspect.getargvalues(frame)
    param_names_values.pop('self', None)
    return param_names_values
