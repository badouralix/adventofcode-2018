from itertools import product

import numpy as np

from tool.runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        serial_number = int(s.strip())
        rack_id = np.arange(1, 301).reshape(-1, 1) + 10
        grid = rack_id * np.arange(1, 301).reshape(1, -1) # broadcasting
        grid += serial_number
        grid *= rack_id
        grid %= 1000
        grid //= 100
        grid -= 5

        X = np.zeros((301, 301))
        # Each cell is the sum of every top left grid cell
        X[1:, 1:] = grid.cumsum(axis=0).cumsum(axis=1) 
        size = 3
        # Each cell is the sum of the size x size square
        tmp = X[size:, size:] + X[:-size, :-size] - X[size:, :-size] - X[:-size, size:] 
        
        x, y = np.unravel_index(tmp.argmax(), tmp.shape)
        return "{},{}".format(x+1, y+1)
