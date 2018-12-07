from runners.python import SubmissionPy
from collections import defaultdict


class BadouralixSubmission(SubmissionPy):

    def run(self, s):
        positions = set()
        for line in s.split("\n"):
            x, y = line.split(", ")
            positions.add((int(x), int(y)))

        left, top, right, bot = self.grid(positions)

        infinite = set()
        grid = dict()
        data = defaultdict(int)

        for i in range(left, right + 1):
            grid[i] = dict()
            for j in range(top, bot + 1):
                grid[i][j] = self.closest_pos(i, j, positions)

                if grid[i][j] is not None:
                    data[grid[i][j]] += 1

                if (i == left or i == right or j == top or j == bot) and grid[i][j] is not None:
                    infinite.add(grid[i][j])

        return max(val for key, val in data.items() if key not in infinite)

    def grid(self, positions):
        left = min(x for (x, _) in positions)
        top = min(y for (_, y) in positions)
        right = max(x for (x, _) in positions)
        bot = max(y for (_, y) in positions)

        return left, top, right, bot

    def closest_pos(self, i, j, positions):
        dist = dict()

        for pos in positions:
            dist[pos] = abs(pos[0] - i) + abs(pos[1] - j)

        result = set(pos for pos in positions if dist[pos] == min(dist.values()))

        if len(result) > 1:
            return None
        return list(result)[0]
