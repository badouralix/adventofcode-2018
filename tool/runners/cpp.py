import errno
import subprocess
import tempfile

from tool.runners.wrapper import SubmissionWrapper
from tool.runners.exceptions import CompilationError, RuntimeError


class SubmissionCpp(SubmissionWrapper):

    def __init__(self, file):
        SubmissionWrapper.__init__(self)
        tmp = tempfile.NamedTemporaryFile(prefix="aoc")
        tmp.close()
        compile_output = subprocess.check_output(["g++", "-Wall", "-Wno-sign-compare", "-O3", "-std=c++14", "-o", tmp.name, file]).decode()
        if compile_output:
            raise CompilationError(compile_output)
        self.executable = tmp.name

    def language(self):
        return 'cpp'

    def exec(self, input):
        try:
            return subprocess.check_output([self.executable, input]).decode()
        except OSError as e:
            if e.errno == errno.ENOENT:
                # executable not found
                return CompilationError(e)
            else:
                # subprocess exited with another error
                return RuntimeError(e)
