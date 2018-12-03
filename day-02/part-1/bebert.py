from runners.python import SubmissionPy
from collections import Counter


class BebertSubmission(SubmissionPy):

    def run(self, s: str):
        twos = 0
        threes = 0
        for line in s.splitlines():
            count = Counter(line.strip())
            if 2 in count.values():
                twos += 1
            if 3 in count.values():
                threes += 1
        return twos * threes
