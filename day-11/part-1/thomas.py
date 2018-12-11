from tool.runners.python import SubmissionPy
import numpy as np


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        serial = int(s)
        grid = np.zeros((301, 301))
        for x in range(1, 301):
            for y in range(1, 301):
                rack_id = x + 10
                grid[x, y] = (rack_id * y + serial) * rack_id
                grid[x, y] = (grid[x, y] % 1000 - grid[x, y] % 100) / 100
                grid[x, y] -= 5

        maxi = float("-inf")
        max_coord = None
        size = 3
        for x in range(1, 301 - size + 1):
            for y in range(1, 301 - size + 1):
                total = np.sum(grid[x : x + size, y : y + size])
                if total > maxi:
                    maxi = total
                    max_coord = (x, y)

        return str(max_coord[0]) + "," + str(max_coord[1])

