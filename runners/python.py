from inspect import getframeinfo, stack
import errno
import subprocess

from .wrapper import SubmissionWrapper


class SubmissionPy(SubmissionWrapper):
    def __init__(self, file):
        SubmissionWrapper.__init__(self)
        self.file = file

    def language(self):
        return "py"

    def exec(self, input):
        try:
            return subprocess.check_output(["python", self.file, input]).decode()
        except OSError as e:
            if e.errno == errno.ENOENT:
                # executable not found
                return None
            else:
                # subprocess exited with another error
                return None

    def __call__(self):
        return SubmissionPy(self.file)
