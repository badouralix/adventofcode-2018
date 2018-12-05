"""
Wrapper class handling the communication between the main python process and
the funky language subprocesses.
"""

from tool.runners.python import SubmissionPy


class SubmissionWrapper(SubmissionPy):

    def __init__(self):
        SubmissionPy.__init__(self)

    # Method that every class implementing SubmssionWrapper should override
    def exec(self, input):
        pass

    def run(self, input):
        stdout = self.exec(input)
        try:
            lines = stdout.split('\n')[:-1]
            if len(lines) > 1:
                print('\n'.join(lines[:-1]))
            return lines[-1]
        except Exception:
            return None
