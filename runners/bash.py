import errno
import subprocess

from .wrapper import SubmissionWrapper


class SubmissionBash(SubmissionWrapper):

    def __init__(self, file):
        SubmissionWrapper.__init__(self)
        self.executable = f"./{file}"

    def language(self):
        return 'sh'

    def exec(self, input):
        try:
            return subprocess.check_output([self.executable, input]).decode()
        except OSError as e:
            if e.errno == errno.ENOENT:
                # executable not found
                return None
            else:
                # subprocess exited with another error
                return None
