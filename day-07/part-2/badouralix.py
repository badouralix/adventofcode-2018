import bisect

from collections import defaultdict
from runners.python import SubmissionPy


WORKERS = 5


class BadouralixSubmission(SubmissionPy):

    def run(self, s):
        reverse_graph = defaultdict(set)
        direct_graph = defaultdict(set)
        remaining_time = dict()

        may_start = set()
        not_start = set()

        for line in s.split("\n"):
            prec = line[5]
            succ = line[36]

            reverse_graph[succ].add(prec)
            direct_graph[prec].add(succ)

            if prec not in remaining_time:
                remaining_time[prec] = ord(prec) - 4
            if succ not in remaining_time:
                remaining_time[succ] = ord(succ) - 4

            may_start.add(prec)
            not_start.add(succ)

        stack = sorted(list(may_start.difference(not_start)))

        assignment = [None] * WORKERS
        working = set()
        done = set()
        t = 0

        while t == 0 or len(stack) != 0 or len(working) != 0:
            t += 1

            for worker in range(WORKERS):
                node = assignment[worker]

                while (node is None or not reverse_graph[node].issubset(done)) and len(stack) != 0:
                    node = stack.pop(0)

                if node is None or not reverse_graph[node].issubset(done):
                    assignment[worker] = None
                    continue

                assignment[worker] = node

            for worker in range(WORKERS):
                node = assignment[worker]

                if node is None:
                    continue
                
                working.add(node)

                remaining_time[node] -= 1

                if remaining_time[node] == 0:
                    assignment[worker] = None
                    working.remove(node)
                    done.add(node)

                    for succ in direct_graph[node]:
                        bisect.insort(stack, succ)
                    stack = list(dict.fromkeys(stack))

        return t
