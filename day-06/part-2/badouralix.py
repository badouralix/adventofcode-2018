from tool.runners.python import SubmissionPy


class BadouralixSubmission(SubmissionPy):

    def run(self, s):
        positions = set()
        for line in s.split("\n"):
            x, y = line.split(", ")
            positions.add((int(x), int(y)))

        left, top, right, bot = self.grid(positions)

        result = 0

        for i in range(left, right + 1):
            for j in range(top, bot + 1):
                if self.sum_dist(i, j, positions) < 10000:
                    result += 1

        return result

    def grid(self, positions):
        left = min(x for (x, _) in positions)
        top = min(y for (_, y) in positions)
        right = max(x for (x, _) in positions)
        bot = max(y for (_, y) in positions)

        return left, top, right, bot

    def sum_dist(self, i, j, positions):
        dist = 0

        for pos in positions:
            dist += abs(pos[0] - i) + abs(pos[1] - j)

        return dist
