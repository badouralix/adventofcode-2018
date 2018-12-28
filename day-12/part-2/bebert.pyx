cpdef long run(s):
    initial_state, moves = s.split("\n\n")
    initial_state = initial_state[15:]

    cdef int i, sign, k, j, tot, old_score, new_score, diff, old_diff, combo

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

    cdef bint pots_old[1000]
    cdef bint pots[1000]

    for i in range(1000):
        pots_old[i] = False
        pots[i] = False

    for i, x in enumerate(initial_state):
        pots_old[200 + i] = x == "#"

    # print("\n" + "".join(["#" if x else "." for x in pots_old]))

    old_score = 0
    old_diff = 0
    combo = 0

    for k in range(201):
        for i in range(5, 995):
            sign = 0
            for j in range(5):
                if pots_old[i + j - 2]:
                    sign += 2**j
            pots[i] = moves_map[sign]

        score = 0
        for i in range(1000):
            if pots[i]:
                score += i - 200
        diff = score - old_score
        if diff == old_diff:
            combo += 1
            # if combo > 30:
            #     print(f"Combo of {diff}; k={k}; score={score}")
        else:
            combo = 0
            old_diff = diff
        old_score = score

        for i in range(1000):
            pots_old[i] = pots[i]

        # print("".join(["#" if x else "." for x in pots]))

    # tot = 0
    # for i in range(1000):
    #     if pots[i]:
    #         tot += i - 200

    return score + diff * (50000000000 - 201)
