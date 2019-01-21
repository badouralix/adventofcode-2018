cpdef int run(s):
    initial_state, moves = s.split("\n\n")
    initial_state = initial_state[15:]

    cdef int i, sign, k, j, tot

    cdef bint moves_map[32]
    for i in range(32):
        moves_map[i] = False

    for line in moves.splitlines():
        sign = 0
        for i in range(5):
            if line[i] == "#":
                sign += 2**i
        moves_map[sign] = line[9] == "#"

    # print(moves_map)

    cdef bint pots_old[200]
    cdef bint pots[200]

    for i in range(200):
        pots_old[i] = False
        pots[i] = False

    for i, x in enumerate(initial_state):
        pots_old[50 + i] = x == "#"

    # print("".join(["#" if x else "." for x in pots]))

    for k in range(20):
        for i in range(10, 190):
            sign = 0
            for j in range(5):
                if pots_old[i + j - 2]:
                    sign += 2**j
            pots[i] = moves_map[sign]

        for i in range(200):
            pots_old[i] = pots[i]
        # print("".join(["#" if x else "." for x in pots]))

    tot = 0
    for i in range(200):
        if pots[i]:
            tot += i - 50
    return tot
