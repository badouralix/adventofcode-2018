#!/usr/bin/env python3

from inspect import getframeinfo, stack


class SubmissionPy:

    def __init__(self):
        self.debug_stack = []

    def language(self):
        return 'py'

    # Method that every class implementing Submssion should override
    def run(self, input):
        pass

    def debug(self, message):
        caller = getframeinfo(stack()[1][0])
        self.debug_stack.append("%s:%d - %s" % (caller.filename, caller.lineno, message))

    def get_debug_stack(self):
        return self.debug_stack

    def cleanup(self):
        pass
