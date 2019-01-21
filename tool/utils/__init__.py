#!/usr/bin/env python3

import os.path


_orig_dir = os.path.dirname(os.path.realpath(__file__))


class BColor:
    """
    BColor printable colors in terminal
    """

    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def mkdirp(path):
    """
    Create directory if it does not exist already.
    path : str name of the directory to be created
    """
    if not os.path.exists(path):
        os.makedirs(path)


def to_ints(strs):
    if not strs:
        return strs
    return list(map(int, strs))


def resolve_path(*path):
    """Resolve any path based on the project root.
    resolve_path('foo', 'bar') will give an absolute path to your_project_directory/foo/bar
    If the path is already absolute, it will stay absolute
    """
    return os.path.abspath(os.path.join(_orig_dir, '..', '..', *path))
