from tool.runners.python import SubmissionPy


def print_grid(grid):
    print("********* BEGINNING *********")
    int_to_char = {0: ".", 1: "=", 2: "|"}
    for line in grid:
        for c in line:
            print(int_to_char[c], end="")
        print()
    print("************ END ***********")
    print()


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        lines = s.splitlines()
        depth = int(lines[0].split()[1])
        target_x, target_y = [int(n) for n in lines[1].split()[1].split(",")]
        erosion = [[0] * (target_y + 1) for _ in range(target_x + 1)]

        res = 0

        erosion[0][0] = depth % 20183
        res += erosion[0][0] % 3
        for x in range(target_x + 1):
            erosion[x][0] = (x * 16807 + depth) % 20183
            res += erosion[x][0] % 3
        for y in range(target_y + 1):
            erosion[0][y] = (y * 48271 + depth) % 20183
            res += erosion[0][y] % 3
        for x in range(1, target_x + 1):
            for y in range(1, target_y + 1):
                erosion[x][y] = (erosion[x - 1][y] * erosion[x][y - 1] + depth) % 20183
                res += erosion[x][y] % 3
        res -= erosion[target_x][target_y] % 3
        erosion[target_x][target_y] = erosion[0][0]
        res += erosion[target_x][target_y] % 3

        return res

