import os
import stat
import subprocess
import tempfile

from .wrapper import SubmissionWrapper


class DependenciesError(Exception):
    pass


class CompilationError(Exception):
    pass


class RuntimeError(Exception):
    pass


class SubmissionGo(SubmissionWrapper):

    def __init__(self, file):
        SubmissionWrapper.__init__(self)
        dep_output = subprocess.check_output(["go", "get", "-d", os.path.join(".", file)]).decode()
        if dep_output:
            raise DependenciesError(dep_output)
        tmp = tempfile.NamedTemporaryFile(prefix="aoc")
        tmp.close()
        compile_output = subprocess.check_output(["go", "build", "-o", tmp.name, file]).decode()
        if compile_output:
            raise CompilationError(compile_output)
        os.chmod(tmp.name, os.stat(tmp.name).st_mode | stat.S_IEXEC)
        self.executable = tmp.name

    def language(self):
        return 'go'

    def exec(self, input):
        try:
            return subprocess.check_output([self.executable, input]).decode()
        except OSError as e:
            if e.errno == os.errno.ENOENT:
                # executable not found
                raise CompilationError(e)
            else:
                # subprocess exited with another error
                raise RuntimeError(e)
