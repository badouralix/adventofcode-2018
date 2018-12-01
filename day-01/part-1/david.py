from runners.python import Submission

class DavidSubmission(Submission):

    def run(self, s):
        result = 0
        for line in s.split("\n"):
            n = int(line[1:])
            result += (n if line[0] == "+" else -n)
        return result
