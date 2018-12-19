cpdef int run(s):
    positions = [line.split(", ") for line in s.splitlines()]
    positions = [(int(_x), int(_y)) for _x, _y in positions]
    positions_x, positions_y = zip(*positions)

    cdef int min_x = min(positions_x)
    cdef int max_x = max(positions_x)
    cdef int min_y = min(positions_y)
    cdef int max_y = max(positions_y)

    cdef int p, dist, near, x, y, dx, dy, i, j

    cdef int grid_mw = 500  # grid max width
    cdef int grid_mh = 500  # grid max height
    cdef int grid_near[500 * 500]
    cdef int grid_dist[500 * 500]

    for p in range(500 * 500):
        grid_near[p] = -1
        grid_dist[p] = 1000000

    for p, (x, y) in enumerate(positions):
        grid_near[grid_mw * (y - min_y) + (x - min_x)] = p
        grid_dist[grid_mw * (y - min_y) + (x - min_x)] = 0

    cdef bint one_grew = True
    still_growing = {p: True for p in range(len(positions))}
    dist = 0
    while one_grew:
        one_grew = False
        dist += 1
        for p, (x, y) in enumerate(positions):
            if not still_growing[p]:
                continue
            p_grew = False

            for dx, dy in list(zip(range(dist), range(-dist, 0))) + \
                          list(zip(range(dist, 0, -1), range(dist))) + \
                          list(zip(range(0, -dist, -1), range(dist, 0, -1))) + \
                          list(zip(range(-dist, 0), range(0, -dist, -1))):
                if x + dx < min_x or y + dy < min_y or x + dx > max_x or y + dy > max_y:
                    continue
                j = x + dx - min_x
                i = y + dy - min_y
                if grid_dist[grid_mw * i + j] == dist:
                    grid_near[grid_mw * i + j] = -1
                    p_grew = True
                elif grid_dist[grid_mw * i + j] > dist:
                    grid_near[grid_mw * i + j] = p
                    grid_dist[grid_mw * i + j] = dist
                    p_grew = True
            if not p_grew:
                still_growing[p] = False
            one_grew = one_grew or p_grew

    infinite = {p: False for p in range(len(positions))}
    infinite[-1] = True

    for i in range(max_x - min_x + 1):
        infinite[grid_near[i]] = True
        infinite[grid_near[grid_mw * (max_y - min_y) + i]] = True

    for i in range(0, grid_mw * (max_y - min_y + 1), grid_mw):
        infinite[grid_near[i]] = True
        infinite[grid_near[i + max_x - min_x]] = True

    count = {p: 0 for p in range(len(positions))}
    for y in range(max_y - min_y + 1):
        for x in range(max_x - min_x + 1):
            i = grid_mw * y + x
            near = grid_near[i]
            if not infinite[near]:
                count[near] += 1

    return max(count.values())
