#!/usr/bin/env python3

# stdlib
import inspect
from importlib.machinery import SourceFileLoader
# project
from tool.runners.bash import SubmissionBash
from tool.runners.c import SubmissionC
from tool.runners.cpp import SubmissionCpp
from tool.runners.go import SubmissionGo
from tool.runners.java import SubmissionJava
from tool.runners.js import SubmissionJs
from tool.runners.cython_aoc import SubmissionPyx
from tool.runners.python import SubmissionPy
from tool.runners.ruby import SubmissionRb
from tool.runners.rust import SubmissionRs
from tool.runners.wrapper import SubmissionWrapper


TOOL_BY_LANGUAGE = {
    'c': 'gcc',
    'cpp': 'g++',
    'go': 'go',
    'java': 'java',
    'js': 'node',
    'py': 'python',
    'pyx': 'cython',
    'rb': 'ruby',
    'rs': 'cargo',
    'sh': 'bash',
}
LANGUAGES = list(TOOL_BY_LANGUAGE.keys())


def ext_by_language(x):
    return '.' + str(x)


def language_by_ext(x):
    return str(x)[1:]


def load_submission_runnable(path, language):
    if language not in LANGUAGES:
        return None
    if language == 'py':
        submission_module = SourceFileLoader('submission_%s' % path, path).load_module()
        classes = inspect.getmembers(submission_module, inspect.isclass)
        for _, cls_submission in classes:
            if issubclass(cls_submission, SubmissionPy) and cls_submission not in (SubmissionPy, SubmissionWrapper):
                return cls_submission()
    elif language == 'pyx':
        return SubmissionPyx(path)
    elif language == 'c':
        return SubmissionC(path)
    elif language == 'cpp':
        return SubmissionCpp(path)
    elif language == 'go':
        return SubmissionGo(path)
    elif language == 'java':
        return SubmissionJava(path)
    elif language == 'js':
        return SubmissionJs(path)
    elif language == 'rb':
        return SubmissionRb(path)
    elif language == 'rs':
        return SubmissionRs(path)
    elif language == 'sh':
        return SubmissionBash(path)
