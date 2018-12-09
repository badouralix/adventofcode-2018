from tool.runners.python import SubmissionPy

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

        dependencies = defaultdict(set)
        reversed_dependencies = defaultdict(set)

        for a,b in relationships:
            dependencies[b].add(a)
            reversed_dependencies[a].add(b)

        activated = set()
        to_visit = sorted(list(set(reversed_dependencies.keys()) - set(dependencies.keys())))
        result = ""

        while len(to_visit)>0:
            item = to_visit.pop(0)
            result += item
            activated.add(item)
            for c in reversed_dependencies[item]:
                if all(dep in activated for dep in dependencies[c]):
                    bisect.insort(to_visit, c)
        return result



