cpdef str run(s):
    cdef int serial = int(s)

    cdef int x, y, q
    cdef int grid[90000]
    for x in range(300):
        for y in range(300):
            grid[y * 300 + x] = (((x + 11) * (y + 1) + serial) * (x + 11) // 100) % 10 - 5

    cdef int max_q = -100
    cdef int max_x = -100
    cdef int max_y = -100

    for x in range(298):
        for y in range(298):
            q = grid[y * 300 + x] + grid[y * 300 + x + 1] + grid[y * 300 + x + 2] + \
                grid[(y + 1) * 300 + x] + grid[(y + 1) * 300 + x + 1] + grid[(y + 1) * 300 + x + 2] + \
                grid[(y + 2) * 300 + x] + grid[(y + 2) * 300 + x + 1] + grid[(y + 2) * 300 + x + 2]
            if q > max_q:
                max_q = q
                max_x = x
                max_y = y

    return f"{max_x + 1},{max_y + 1}"
