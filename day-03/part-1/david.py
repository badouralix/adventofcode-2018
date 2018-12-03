from runners.python import SubmissionPy

from collections import defaultdict

class DavidSubmission(SubmissionPy):

    def parse_line(self, line):
        claim_id, _, origin, size = line.split(" ")
        x0,y0 = [int(x) for x in origin[:-1].split(",")]
        l1,l2 = [int(x) for x in size.split("x")]
        return int(claim_id[1:]), x0, y0, l1, l2

    def run(self, s):
        d = defaultdict(int)
        for l in s.split("\n"):
            _, x0, y0, l1, l2 = self.parse_line(l)
            for i in range(l1):
                for j in range(l2):
                    d[(x0+i,y0+j)] += 1

        return sum(1 for v in d.values() if v >= 2)