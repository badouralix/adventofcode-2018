from runners.python import SubmissionPy

class DavidSubmission(SubmissionPy):

    def run(self, s):
        seen = set()
        x = 0
        while x not in seen:
            for line in s.split("\n"):
                n = int(line[1:])
                x += (n if line[0] == "+" else -n)
        return x
