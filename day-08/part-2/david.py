from runners.python import SubmissionPy

import itertools
from collections import defaultdict

class DavidSubmission(SubmissionPy):

    def score_tree(self, items):
        children, metadata = next(items), next(items)
        if children == 0:
            score = 0
            for _ in range(metadata):
                score += next(items)
            return score

        scores = [self.score_tree(items) for _ in range(children)]
        indexes = [next(items) for _ in range(metadata)]
        return sum(scores[i-1] for i in indexes if i <= len(scores))


    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        items = (int(x) for x in s.split(" "))

        return self.score_tree(items)

