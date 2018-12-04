import sys

from collections import defaultdict

class Submission():

    def parse_line(self, line):
        claim_id, _, origin, size = line.split(" ")
        x0,y0 = [int(x) for x in origin[:-1].split(",")]
        l1,l2 = [int(x) for x in size.split("x")]
        return int(claim_id[1:]), x0, y0, l1, l2

    def run(self, s):
        grid = [[0 for _ in range(1000)] for _ in range(1000)]
        for l in s.split("\n"):
            claim_id, x0, y0, l1, l2 = self.parse_line(l)
            for i in range(l1):
                for j in range(l2):
                    grid[x0+i][y0+j] += 1

        for l in s.split("\n"):
            claim_id, x0, y0, l1, l2 = self.parse_line(l)
            if all(grid[x0+i][y0+j] == 1 for i in range(l1) for j in range(l2)):
                return claim_id

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
