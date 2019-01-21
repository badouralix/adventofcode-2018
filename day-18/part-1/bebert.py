from tool.runners.python import SubmissionPy


class BebertSubmission(SubmissionPy):

    def run(self, s):
        legend = {".": 1, "|": 2, "#": 3}
        grid_h = 50 + 2
        grid_w = 50 + 2
        n_minutes = 10

        grid_old = [0] * grid_h * grid_w
        grid = [0] * grid_h * grid_w

        for j, line in enumerate(s.splitlines()):
            for i, x in enumerate(line.strip()):
                grid_old[(j + 1) * grid_w + i + 1] = legend.get(x)

        around = [0, 0, 0, 0]  # nope, open, tree, lumbyard

        for n in range(n_minutes):
            for k, x in enumerate(grid_old):
                if x > 0:
                    around = [0, 0, 0, 0]
                    around[grid_old[k - grid_w - 1]] += 1
                    around[grid_old[k - grid_w]] += 1
                    around[grid_old[k - grid_w + 1]] += 1
                    around[grid_old[k - 1]] += 1
                    around[grid_old[k + 1]] += 1
                    around[grid_old[k + grid_w - 1]] += 1
                    around[grid_old[k + grid_w]] += 1
                    around[grid_old[k + grid_w + 1]] += 1
                    if x == 1 and around[2] > 2:
                        grid[k] = 2
                    elif x == 2 and around[3] > 2:
                        grid[k] = 3
                    elif x == 3 and (around[3] == 0 or around[2] == 0):
                        grid[k] = 1
                    else:
                        grid[k] = x

            for k, x in enumerate(grid):
                grid_old[k] = x

        around = [0, 0, 0, 0]
        for x in grid:
            around[x] += 1

        return around[2] * around[3]
