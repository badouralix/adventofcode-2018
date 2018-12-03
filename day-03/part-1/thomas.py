from runners.python import SubmissionPy
import numpy as np


class ThomasSubmission(SubmissionPy):
    @staticmethod
    def get_claim(line):
        _, _, border_dist, dim = line.split()
        left_dist, top_dist = [int(d) for d in border_dist[:-1].split(",")]
        width, height = [int(x) for x in dim.split("x")]
        return (top_dist, top_dist + height, left_dist, left_dist + width)

    def run(self, s):
        fabric = np.zeros((1000, 1000))
        for line in s.split("\n"):
            imin, imax, jmin, jmax = self.get_claim(line)
            fabric[imin:imax, jmin:jmax] += 1
        return np.count_nonzero(fabric > 1)
