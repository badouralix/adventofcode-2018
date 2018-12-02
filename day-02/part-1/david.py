from runners.python import SubmissionPy

from collections import Counter

class DavidSubmission(SubmissionPy):

    def run(self, s):
        words = s.split("\n")
        appears2, appears3 = (0,0)
        for w in words:
            c = Counter(w)
            if 2 in c.values():
                appears2 += 1
            if 3 in c.values():
                appears3 += 1

        return appears2 * appears3
