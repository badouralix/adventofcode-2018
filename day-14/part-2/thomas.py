from tool.runners.python import SubmissionPy
import numpy as np


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        puzzle_input = [int(c) for c in s]
        recipes = [3, 7]
        elves = [0, 1]
        found_from = None
        while found_from is None:
            if np.array_equal(recipes[-len(puzzle_input) - 1 : -1], puzzle_input):
                found_from = -len(puzzle_input) - 1
                break
            if np.array_equal(recipes[-len(puzzle_input) :], puzzle_input):
                found_from = -len(puzzle_input)
                break
            new = recipes[elves[0]] + recipes[elves[1]]
            recipes += [int(c) for c in str(new)]
            elves = [
                (elves[0] + 1 + recipes[elves[0]]) % len(recipes),
                (elves[1] + 1 + recipes[elves[1]]) % len(recipes),
            ]
        return str(len(recipes) + found_from)
