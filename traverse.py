#!/usr/bin/env python3
"""
Functions that aid traversion of a given directory with ignore patterns.

Use like:
  try;
      patterns = compile_patterns(<my_pattern_list>)
      for path in yield_paths(<root_dir>, <my_pattern_list>):
          print(path)
  except RegexCompileError ar err:
      print(err)
"""

import os
import pathlib
import re
from collections.abc import Iterable


class RegexCompileError(re.error):
    """May be thrown when a regex could not be compiled."""

    def __init__(self, pattern, msg, pos) -> None:
        message = f'Could not compile pattern "{pattern}": {msg}, at {pos}.'
        super().__init__(message)


def compile_patterns(patterns: Iterable[str]) -> set[re.Pattern]:
    """Retrieve a set of compiled patterns from given regex patterns."""
    compiled_pattern = set()
    for pattern in patterns:
        try:
            compiled_pattern.add(re.compile(pattern))
        except re.error as err:
            raise RegexCompileError(err.pattern, err.msg, err.pos)
    return compiled_pattern


def match_any(string: str, patterns: Iterable[re.Pattern]) -> bool:
    """Safely check if the given string matches any of the given regexes."""
    if not patterns or not string:
        return False
    return any(re.match(p, string) for p in patterns)


def yield_paths(
    root: pathlib.Path, ignore_patterns: Iterable[re.Pattern] = None
) -> Iterator[pathlib.Path]:
    """Yield all relative folder paths and file paths below a given path."""
    for dir_path, _, files in os.walk(root):
        if match_any(dir_path, ignore_patterns):
            continue
        yield pathlib.Path(dir_path).relative_to(root)
        for file in files:
            if match_any(file, ignore_patterns):
                continue
            yield pathlib.Path(dir_path, file).relative_to(root)
