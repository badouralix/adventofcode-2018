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
    values = []

    for _ in range(nbSub):
        rest, v = parse(rest)
        values.append(v)

    metas = rest[:nbMeta]
    rest = rest[nbMeta:]

    if nbSub == 0:
        return rest, sum(metas)
    else:
        return rest, sum(values[m-1] if m <= len(values) else 0 for m in metas)
