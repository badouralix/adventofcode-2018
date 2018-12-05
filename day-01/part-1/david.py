from tool.runners.python import SubmissionPy

class DavidSubmission(SubmissionPy):

    def run(self, s):
        result = 0
        for line in s.split("\n"):
            n = int(line[1:])
            result += (n if line[0] == "+" else -n)
        return result
