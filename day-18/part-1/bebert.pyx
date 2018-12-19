cpdef int run(s):
    legend = {".": 1, "|": 2, "#": 3}
    cdef int i, j, k, a, x, n

    cdef int grid_h = 50 + 2
    cdef int grid_w = 50 + 2
    cdef int n_minutes = 10

    cdef int grid_old[2704]
    cdef int grid[2704]

    for k in range(2704):
        grid_old[k] = 0
        grid[k] = 0

    for j, line in enumerate(s.splitlines()):
        for i, c in enumerate(line.strip()):
            grid_old[(j + 1) * grid_w + i + 1] = legend.get(c)

    cdef int around[4]  # nope, open, tree, lumbyard

    for n in range(n_minutes):
        for k in range(2704):
            x = grid_old[k]
            if x > 0:
                for a in range(4):
                    around[a] = 0
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

        for k in range(2704):
            grid_old[k] = grid[k]

    for a in range(4):
        around[a] = 0

    for e in grid:
        around[e] += 1

    return around[2] * around[3]
