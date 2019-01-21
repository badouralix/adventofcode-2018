from tool.runners.python import SubmissionPy
import collections


class JonSubmission(SubmissionPy):

    def run(self, s):
        _, t = parse([int(x) for x in s.split(" ")])
        return t

def parse(l):
    nbSub = l[0]
    nbMeta = l[1]

    rest = l[2:]
    total = 0

    for i in range(nbSub):
        rest, sumMeta = parse(rest)
        total += sumMeta

    for i in range(nbMeta):
        total += rest[i]

    return rest[nbMeta:], total
