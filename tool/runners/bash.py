import errno
import os
import stat
import subprocess

from tool.runners.wrapper import SubmissionWrapper


class SubmissionBash(SubmissionWrapper):

    def __init__(self, file):
        SubmissionWrapper.__init__(self)
        self.executable = f"./{file}"
        os.chmod(self.executable, os.stat(self.executable).st_mode | stat.S_IEXEC)

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
