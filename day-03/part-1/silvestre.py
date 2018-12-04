import sys
import re
import numpy as np

class Submission():

    def parse(self, s):
        # "#1400 @ 873,28: 11x27"
        rec = re.compile(r"^#(\d+) @ (\d+),(\d+): (\d+)x(\d+)$")
        rectangles = [rec.match(row) for row in s.splitlines()]
        rectangles = [tuple(map(int, m.groups())) for m in rectangles]
        return rectangles

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        rectangles = self.parse(s) # list of (id, x, y, width, height)
        array = np.zeros((1000, 1000), dtype=np.uint)
        for (_, x, y, width, height) in rectangles:
            array[x:x+width, y:y+height] += 1

        return np.sum(array >= 2)

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
