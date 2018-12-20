# def export_grid(grid, count=None):
#     grid_w = 2000
#     with open("tmp_bebert.txt.save", "w") as f:
#         for i in range(0, len(grid), grid_w):
#             line = "".join("x#~.|+O"[x] for x in grid[i:i+grid_w]) + "\n"
#             f.write(line)
#         if count:
#             f.write("\n" + str(count))
#     return


cpdef int run(s):
    cdef int k, x, y

    cdef int grid_h = 2500
    cdef int grid_w = 1000

    cdef int grid[2500 * 1000]  # grid_h * grid_w

    for k in range(grid_h * grid_w):
        grid[k] = 3

    cdef int min_y = grid_h
    cdef int max_y = 0

    # 0 out of range, 1 clay, 2 water, 3 sand, 4 wet sand

    for line in s.splitlines():
        short, long = line.split(", ")
        if short.startswith("x="):
            x = int(short.split("=")[1])
            y0s, y1s = long.split("=")[1].split("..")
            y0, y1 = int(y0s), int(y1s)
            for y in range(y0, y1 + 1):
                grid[grid_w * y + x] = 1
            if y0 < min_y:
                min_y = y0
            if y1 > max_y:
                max_y = y0

        elif short.startswith("y="):
            y = int(short.split("=")[1])
            x0, x1 = long.split("=")[1].split("..")
            for x in range(int(x0), int(x1) + 1):
                grid[grid_w * y + x] = 1
            if y < min_y:
                min_y = y
            if y > max_y:
                max_y = y

    for k in range((max_y + 1) * grid_w, grid_h * grid_w):
        grid[k] = 0

    cdef int stack[10000]
    cdef int stack_cur = 0
    stack[0] = 500

    grid[500] = 4
    cdef int current, right, left
    cdef bint right_blocked, left_blocked

    cdef int count = 0
    while stack_cur >= 0:
        current = stack[stack_cur]
        if grid[current] == 0:
            column = current % grid_w
            while current % grid_w == column:
                stack_cur -= 1
                current = stack[stack_cur]
            continue

        while grid[current + grid_w] == 3:
            if grid[current] == 3 and current > min_y * grid_w:
                count += 1
            grid[current] = 4
            current = current + grid_w
            if current >= (max_y + 1) * grid_w:
                stack_cur -= 1
                break
            stack_cur += 1
            stack[stack_cur] = current
        stack_cur -= 1
        if grid[current + grid_w] == 0 or grid[current + grid_w] == 4:
            if grid[current] == 3:
                count += 1
            grid[current] = 4
            continue

        right_blocked = False
        right = current
        while grid[right + grid_w] == 1 or grid[right + grid_w] == 2:
            if grid[right] == 3:
                count += 1
            grid[right] = 4
            if grid[right + 1] == 1:
                right_blocked = True
                break
            right += 1

        left_blocked = False
        left = current
        while grid[left + grid_w] == 1 or grid[left + grid_w] == 2:
            if grid[left] == 3:
                count += 1
            grid[left] = 4
            if grid[left - 1] == 1:
                left_blocked = True
                break
            left -= 1

        if right_blocked and left_blocked:
            for x in range(left, right + 1):
                if grid[x] == 3:
                    count += 1
                grid[x] = 2

        if not left_blocked:
            if grid[left] == 3:
                count += 1
            grid[left] = 4
            stack_cur += 1
            stack[stack_cur] = left

        if not right_blocked:
            if grid[right] == 3:
                count += 1
            grid[right] = 4
            stack_cur += 1
            stack[stack_cur] = right

    # grid[current] = 6
    # export_grid(grid, count=count)

    # cdef int count2 = 0
    # for k in range(min_y * grid_w, (max_y + 1) * grid_w):
    #     if grid[k] == 2 or grid[k] == 4:
    #         count2 += 1
    #
    # print(count, count2)

    return count
