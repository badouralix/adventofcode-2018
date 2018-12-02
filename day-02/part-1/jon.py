from runners.python import SubmissionPy
from collections import Counter

class JonSubmission(SubmissionPy):

    def run(self, s):

        c2 = 0
        c3 = 0

        for l in s.splitlines():
            c = Counter(l.strip())
            if 2 in c.values():
                c2 += 1
            if 3 in c.values():
                c3 += 1

        return c2 * c3
