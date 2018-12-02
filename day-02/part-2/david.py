from runners.python import SubmissionPy

from itertools import combinations

class DavidSubmission(SubmissionPy):

    def distance(self, w1, w2):
        # returns the distance between two words
        # it is the number of letters for which the two words differ
        return sum(1 if w1[i] != w2[i] else 0 for i in range(len(w1)))

    def run(self, s):
        words = s.split("\n")
        n = len(words[0])
        for w1, w2 in combinations(words, 2):
            if self.distance(w1, w2) == 1:
                return "".join(w1[i] for i in range(n) if w1[i]==w2[i])
