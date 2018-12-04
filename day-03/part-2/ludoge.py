import sys


class Claim:
    def __init__(self, data):
        self.id = int(data.split()[0][1:])
        _x0, _y0 = data.split()[2].replace(":", "").split(",")
        self.x0, self.y0 = int(_x0), int(_y0)
        _width, _height = data.split()[3].split("x")
        self.width, self.height = int(_width), int(_height)
        self.squares = set([(i, j)
                            for i in range(self.x0, self.x0 + self.width)
                            for j in range(self.y0, self.y0 + self.height)])

    def overlaps(self, other_claim):
        return bool(self.squares.intersection(other_claim.squares))


class Grid:
    def __init__(self):
        self.occupied_squares = set()
        self.overlapping_squares = set()
        self.claims = set()
        self.free_claims = set()

    def add_claim(self, claim):
        self.claims.add(claim)
        newly_overlapping = self.occupied_squares.intersection(claim.squares)
        self.overlapping_squares.update(newly_overlapping)
        self.occupied_squares.update(claim.squares)
        if not newly_overlapping:
            self.free_claims.add(claim)
        else:
            for free_claim in set(self.free_claims):
                if free_claim.overlaps(claim):
                    self.free_claims.remove(free_claim)

class Submission():

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        grid = Grid()
        for line in s.splitlines():
            grid.add_claim(Claim(line))

        return list(grid.free_claims)[0].id

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
