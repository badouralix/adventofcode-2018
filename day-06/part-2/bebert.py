from tool.runners.python import SubmissionPy


class BebertSubmission(SubmissionPy):

    def run(self, s):
        positions = [line.split(", ") for line in s.splitlines()]
        positions = [(int(x), int(y)) for x, y in positions]
        # print(positions)

        obj_less = 10000  # if len(positions) != 6 else 32

        min_x = min(positions, key=lambda p: p[0])[0]
        max_x = max(positions, key=lambda p: p[0])[0]
        min_y = min(positions, key=lambda p: p[1])[1]
        max_y = max(positions, key=lambda p: p[1])[1]
        # print(min_x, max_x, min_y, max_y)

        grid = [[]] * (max_y - min_y + 1)
        for y in range(max_y - min_y + 1):
            grid[y] = [0] * (max_x - min_x + 1)

        for p, (x, y) in enumerate(positions):
            for dx in range(max_x - x + 1):
                for dy in range(max_y - y + 1):
                    j = x + dx - min_x
                    i = y + dy - min_y
                    grid[i][j] += dx + dy
                for dy in range(1, y - min_y + 1):
                    j = x + dx - min_x
                    i = y - dy - min_y
                    grid[i][j] += dx + dy
            for dx in range(1, x - min_x + 1):
                for dy in range(max_y - y + 1):
                    j = x - dx - min_x
                    i = y + dy - min_y
                    grid[i][j] += dx + dy
                for dy in range(1, y - min_y + 1):
                    j = x - dx - min_x
                    i = y - dy - min_y
                    grid[i][j] += dx + dy

        count = 0
        for line in grid:
            for d in line:
                if d < obj_less:
                    count += 1

        return count
