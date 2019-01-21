cpdef str run(s):
    cdef int serial = int(s)

    cdef int x, y, q, r, dx, dy
    cdef int grid[90000]
    for x in range(300):
        for y in range(300):
            grid[y * 300 + x] = (((x + 11) * (y + 1) + serial) * (x + 11) // 100) % 10 - 5

    cdef int max_q = -100
    cdef int max_x = -100
    cdef int max_y = -100
    cdef int max_r = 1

    for x in range(300):
        for y in range(300):
            q = 0
            for r in range(300 - max(x, y)):
                for dx in range(r + 1):
                    q += grid[(y + r) * 300 + x + dx]
                for dy in range(r):
                    q += grid[(y + dy) * 300 + x + r]

                if q > max_q:
                    max_q = q
                    max_x = x
                    max_y = y
                    max_r = r

    return f"{max_x + 1},{max_y + 1},{max_r + 1}"
