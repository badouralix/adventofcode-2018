"""
Wrapper class handling the communication between the main python process and
the funky language subprocesses.
"""
from inspect import getframeinfo, stack


class SubmissionWrapper:
    def __init__(self):
        self.debug_stack = []

    def language(self):
        return "py"

    def debug(self, message):
        caller = getframeinfo(stack()[1][0])
        self.debug_stack.append(
            "%s:%d - %s" % (caller.filename, caller.lineno, message)
        )

    def get_debug_stack(self):
        return self.debug_stack

    # Method that every class implementing SubmssionWrapper should override
    def exec(self, input):
        pass

    def run(self, input):
        stdout = self.exec(input)
        try:
            lines = stdout.split("\n")[:-1]
            if len(lines) > 1:
                print("\n".join(lines[:-1]))
            return lines[-1]
        except Exception:
            return None
