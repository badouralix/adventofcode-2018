from collections import defaultdict

import numpy as np
from tool.runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        """don't cover a side case"""
        points = np.array([line.split(', ') for line in s.splitlines()], dtype="int16")
        x_min, y_min = np.min(points, axis=0)
        x_max, y_max = np.max(points, axis=0)
        areas = defaultdict(int)
        infinite = set()
        for i in range(x_min, x_max+1):
            for j in range(y_min, y_max+1):
                curr = self.closest_point(i, j, points)
                areas[curr] += 1
                if i == x_min or i == x_max or j == y_min or j == y_max:
                    infinite.add(curr)
        return max(areas[key] for key in areas if key not in infinite)

    def closest_point(self, i, j, points):
        dist = np.abs(points - [i, j])
        dist = np.sum(dist, axis=1)
        ret = np.argmin(dist)
        cond = np.count_nonzero(dist[ret:] == dist[ret]) == 1
        return ret if cond else None
