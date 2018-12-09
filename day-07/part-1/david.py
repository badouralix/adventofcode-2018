from runners.python import SubmissionPy

from collections import defaultdict
from string import ascii_uppercase
import bisect

class DavidSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        relationships = []
        for line in s.split("\n"):
            x = line.split(" ")
            relationships.append((x[1], x[7]))

        successors = defaultdict(set)
        parents = defaultdict()
        for a,b in relationships:
            successors[a].add(b)
            parents[b].add(b)


        ready = sorted(list(set(parent.keys()) - set(successors.keys())))
        visited = set()
        result = ""
        while len(ready) > 0:
            item = ready.pop(0)
            result += item
            for child in successors[item]:
                bisect.insort(ready, child)
            if len(successors[item]) == 0:
                break

        return result




