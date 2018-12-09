#!/usr/bin/env python3


import os.path


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
