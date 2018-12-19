import errno
import subprocess
import tempfile

from tool.runners.wrapper import SubmissionWrapper
from tool.runners.exceptions import CompilationError, RuntimeError


class SubmissionJava(SubmissionWrapper):

    def __init__(self, file):
        SubmissionWrapper.__init__(self)
        # Create a temporary directory to put the compiled java in,
        # in order to have it destroyed once we are done
        self.temporary_directory = tempfile.mkdtemp(prefix="aoc")
        compile_output = subprocess.check_output(["javac", file, "-d", self.temporary_directory]).decode()
        if compile_output:
            raise CompilationError(compile_output)

    def language(self):
        return 'java'

    def exec(self, input):
        try:
            # main class MUST be named Solution
            return subprocess.check_output(["java", "-cp", self.temporary_directory, "Solution", input]).decode()
        except OSError as e:
            if e.errno == errno.ENOENT:
                # executable not found
                return CompilationError(e)
            else:
                # subprocess exited with another error
                return RuntimeError(e)
