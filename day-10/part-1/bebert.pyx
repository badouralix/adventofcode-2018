import numpy as np


def print_grid(grid):
    res = ""
    for line in grid:
        res += "".join(["#" if s else " " for s in line]) + "\n"
    print(res)


signatures = {
    231: "F",
    295: "P",
    360: "L",
    375: "C",
    470: "J",
    490: "Z",
    491: "E",
    525: "X",
    564: "R",
    621: "H",
    639: "A",
    673: "G",
    707: "B",
    755: "N",
}


def identify(letter_grid):
    # Make signature
    sign = 0
    for j, line in enumerate(letter_grid):
        for i, x in enumerate(line):
            if x:
                sign += (i + 1) * (j + 1) + i + j

    # Compare signatures
    if sign in signatures:
        return signatures[sign]
    print("Count not recognize the letter with signature:", sign, "(plz add me in day-10/part-1/bebert.pyx :3)")
    print_grid(letter_grid)
    return "?"


cpdef str run(s):
    cdef int i, x, y

    cdef int x_positions[500]
    cdef int y_positions[500]
    cdef int x_velocity[500]
    cdef int y_velocity[500]
    cdef int nb_stars = 0

    for i, line in enumerate(s.splitlines()):
        nb_stars += 1
        a, b, c, d = line[10:-1].replace("> velocity=<", ",").split(",")
        x_positions[i] = int(a)
        y_positions[i] = int(b)
        x_velocity[i] = int(c)
        y_velocity[i] = int(d)

    cdef int min_x = 1000
    cdef int max_x = -1000
    cdef int min_y = 1000
    cdef int max_y = -1000
    cdef int total_steps = 0

    while abs(max_y - min_y) > 10:
        # Reset min and max
        min_x = 1000
        max_x = -1000
        min_y = 1000
        max_y = -1000

        # Move stars
        for i in range(nb_stars):
            x_positions[i] += x_velocity[i]
            y_positions[i] += y_velocity[i]

            if x_positions[i] < min_x:
                min_x = x_positions[i]
            if x_positions[i] > max_x:
                max_x = x_positions[i]
            if y_positions[i] < min_y:
                min_y = y_positions[i]
            if y_positions[i] > max_y:
                max_y = y_positions[i]

        total_steps += 1
        # print(abs(max_y - min_y))

    cdef int grid_w = max_x - min_x + 1
    cdef int grid_h = max_y - min_y + 1
    cdef unsigned char[:, :] grid

    grid = np.zeros((grid_h, grid_w), dtype=np.uint8)
    for i in range(nb_stars):
        grid[y_positions[i] - min_y, x_positions[i] - min_x] = 1

    # res = ""
    # for line in grid:
    #     res += "".join(["#" if s else " " for s in line]) + "\n"
    # print(res)
    # print("New letters:", new_letters)

    letters = ""
    for x in range(0, max_x - min_x, 8):
        letters += identify(grid[:, x: x+6])

    return letters
