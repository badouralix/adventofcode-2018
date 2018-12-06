import numpy as np
from runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        """don't cover a side case"""
        points = np.array([line.split(', ') for line in s.splitlines()], dtype="int16")
        x_min, y_min = np.min(points, axis=0)
        x_max, y_max = np.max(points, axis=0)

        ret = 0
        for i in range(x_min, x_max+1):
            for j in range(y_min, y_max+1):
                if np.abs(points - [i, j]).sum() < 10000:
                    ret += 1
        return ret

