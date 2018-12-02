from runners.python import SubmissionPy


class BebertSubmission(SubmissionPy):

    def run(self, s):
        a = 0
        for line in s.splitlines():
            x = int(line.strip())
            a += x

        return a
