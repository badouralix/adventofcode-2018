from tool.runners.python import SubmissionPy

from collections import defaultdict

class DavidSubmission(SubmissionPy):

    def parse_line(self, line):
        claim_id, _, origin, size = line.split(" ")
        x0,y0 = [int(x) for x in origin[:-1].split(",")]
        l1,l2 = [int(x) for x in size.split("x")]
        return int(claim_id[1:]), x0, y0, l1, l2

    def run(self, s):
        grid = [[0 for _ in range(1000)] for _ in range(1000)]
        result = 0
        for l in s.split("\n"):
            _, x0, y0, l1, l2 = self.parse_line(l)
            for i in range(l1):
                for j in range(l2):
                    grid[x0+i][y0+j] += 1
                    if grid[x0+i][y0+j] == 2:
                        result += 1


        return result
