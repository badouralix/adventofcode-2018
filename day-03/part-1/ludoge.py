from tool.runners.python import SubmissionPy


class Claim:
    def __init__(self, data):
        _x0, _y0 = data.split()[2].replace(":", "").split(",")
        self.x0, self.y0 = int(_x0), int(_y0)
        _width, _height = data.split()[3].split("x")
        self.width, self.height = int(_width), int(_height)
        self.squares = set([(i, j)
                            for i in range(self.x0, self.x0 + self.width)
                            for j in range(self.y0, self.y0 + self.height)])


class Grid:
    def __init__(self):
        self.occupied_squares = set()
        self.overlapping_squares = set()

    def add_claim(self, claim):
        newly_overlapping = self.occupied_squares.intersection(claim.squares)
        self.overlapping_squares.update(newly_overlapping)
        self.occupied_squares.update(claim.squares)

class LudogeSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        grid = Grid()
        for line in s.splitlines():
            grid.add_claim(Claim(line))

        return len(grid.overlapping_squares)


