cpdef int run(s):
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

    # cdef int grid_w = max_x - min_x + 1
    # cdef int grid_h = max_y - min_y + 1
    # cdef unsigned char[:, :] grid
    #
    # grid = np.zeros((grid_h, grid_w), dtype=np.uint8)
    # for i in range(nb_stars):
    #     grid[y_positions[i] - min_y, x_positions[i] - min_x] = 1

    # res = ""
    # for line in grid:
    #     res += "".join(["#" if s else " " for s in line]) + "\n"
    # print(res)

    return total_steps
