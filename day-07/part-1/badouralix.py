import bisect

from collections import defaultdict
from runners.python import SubmissionPy


class BadouralixSubmission(SubmissionPy):

    def run(self, s):
        reverse_graph = defaultdict(set)
        direct_graph = defaultdict(set)

        may_start = set()
        not_start = set()

        for line in s.split("\n"):
            prec = line[5]
            succ = line[36]

            reverse_graph[succ].add(prec)
            direct_graph[prec].add(succ)

            may_start.add(prec)
            not_start.add(succ)

        stack = sorted(list(may_start.difference(not_start)))
        result = ""
        done = set(result)

        while len(stack) != 0:
            node = stack.pop(0)

            if node not in done and reverse_graph[node].issubset(done):
                result += node
                done.add(node)

                for succ in direct_graph[node]:
                    bisect.insort(stack, succ)

        return result
