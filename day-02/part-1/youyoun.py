from tool.runners.python import SubmissionPy
from collections import Counter


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        threes = 0
        twos = 0
        for e in s.splitlines():
            c = Counter(e)
            c_values = c.values()
            if 2 in c_values:
                twos += 1
            if 3 in c_values:
                threes += 1
        return twos * threes
