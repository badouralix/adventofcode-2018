import re
import numpy as np
from runners.python import SubmissionPy

class SilvestreSubmission(SubmissionPy):

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
        for (id_rec, x, y, width, height) in rectangles:
            array[x:x+width, y:y+height] += 1

        for (id_rec, x, y, width, height) in rectangles:
            if np.all(array[x:x+width, y:y+height] == 1):
                return id_rec
