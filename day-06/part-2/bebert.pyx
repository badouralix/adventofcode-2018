cpdef int run(s):
    positions = [line.split(", ") for line in s.splitlines()]
    positions = [(int(_x), int(_y)) for _x, _y in positions]
    positions_x, positions_y = zip(*positions)

    cdef int min_x = min(positions_x)
    cdef int max_x = max(positions_x)
    cdef int min_y = min(positions_y)
    cdef int max_y = max(positions_y)

    cdef int p, x, y, dx, dy, i, j

    cdef int grid_mw = 500  # grid max width
    cdef int grid_mh = 500  # grid max height
    cdef int grid_lin[500 * 500]

    for p in range(500 * 500):
        grid_lin[p] = 0

    for p, (x, y) in enumerate(positions):
        for dx in range(max_x - x + 1):
            for dy in range(max_y - y + 1):
                j = x + dx - min_x
                i = y + dy - min_y
                grid_lin[grid_mw * i + j] += dx + dy
            for dy in range(1, y - min_y + 1):
                j = x + dx - min_x
                i = y - dy - min_y
                grid_lin[grid_mw * i + j] += dx + dy
        for dx in range(1, x - min_x + 1):
            for dy in range(max_y - y + 1):
                j = x - dx - min_x
                i = y + dy - min_y
                grid_lin[grid_mw * i + j] += dx + dy
            for dy in range(1, y - min_y + 1):
                j = x - dx - min_x
                i = y - dy - min_y
                grid_lin[grid_mw * i + j] += dx + dy

    cdef int obj_less = 10000  # if len(positions) != 6 else 32
    cdef int count = 0
    for y in range(max_y - min_y + 1):
        for x in range(max_x - min_x + 1):
            if grid_lin[grid_mw * y + x] < obj_less:
                count += 1

    return count
