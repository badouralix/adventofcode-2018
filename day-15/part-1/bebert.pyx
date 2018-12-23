# === Display or export functions ===

def print_grid(grid, grid_w, step=None):
    fname = "output.save/15_1_grid.txt" if step is None else "output.save/15_2_grid_{:06d}.txt".format(step)
    with open(fname, "w") as f:
        for i in range(0, len(grid), grid_w):
            line = "".join("x#.EG"[x] for x in grid[i:i+grid_w]) + "\n"
            f.write(line)
    return 0


def print_grid_hp(grid, mobs, grid_w, step=None):
    lines = []
    for i in range(0, len(grid), grid_w):
        lines.append("".join("x#.EG"[x] for x in grid[i:i+grid_w]))

    pos_hp = []
    for i in range(len(mobs)):
        if mobs[i].get("type") > 0:
            pos_hp.append((mobs[i].get("pos"), mobs[i].get("hp")))
    pos_hp.sort()

    for pos, hp in pos_hp:
        lines[pos // grid_w] += " " + str(hp)

    fname = "output.save/15_1_grid.txt" if step is None else "output.save/15_2_grid_{:06d}.txt".format(step)
    with open(fname, "w") as f:
        f.write("\n".join(lines))
    return 0


def print_dist(dist, grid_w):
    print("")
    for i in range(0, len(dist), grid_w):
        print(" ".join(f"{x:3d}" if x < 1000 else "###" for x in dist[i:i+grid_w]))
    return 0


# === Actual code ===

cdef struct Mob:
    unsigned char type
    unsigned char hp
    int pos
    bint played


DEF GRID_H = 32
DEF GRID_W = 32
DEF GRID_SIZE = 1024

DEF MOB_LIST_SIZE = 60

DEF HP_INF = 1000
DEF DIST_INF = 1000

cdef int around[4]
around[:] = [-GRID_W, -1, 1, GRID_W]
cdef int r
cdef bint reduced


cdef void fill_distances(int *grid, int *dist, int target):
    reduced = False
    for r in around:
        if dist[target + r] + 1 < dist[target]:
            dist[target] = dist[target + r] + 1
            reduced = True

    if reduced:
        for r in around:
            if grid[target + r] == 2:
                fill_distances(grid, dist, target + r)


cpdef int run(s):
    legend = {"#": 1, ".": 2, "E": 3, "G": 4}
    cdef Mob empty_mob = Mob(type=0, hp=0, pos=0, played=True)

    cdef int x, y, e, i, j
    cdef int min_hp, min_dist, min_pos, mov_pos, steps
    cdef bint found_opp = True

    cdef int grid[GRID_SIZE]
    cdef int dist[GRID_SIZE]

    for e in range(GRID_SIZE):
        grid[e] = 1

    cdef Mob mobs[MOB_LIST_SIZE]
    cdef int mobs_len = 0
    for e in range(MOB_LIST_SIZE):
        mobs[e] = empty_mob

    cdef int type_count[5]
    for i in range(5):
        type_count[i] = 0

    cdef Mob *cur_mob
    cdef Mob *cur_tst
    cdef Mob *cur_opp
    cdef int opp_type

    # === Fill the grid by parsing the input ===
    for y, line in enumerate(s.splitlines()):
        for x, c in enumerate(line.strip()):
            e = legend[c]
            grid[y * GRID_W + x] = e
            if e == 3 or e == 4:
                mobs[mobs_len] = Mob(type=e, hp=200, pos=y * GRID_W + x, played=False)
                mobs_len += 1
                type_count[e] += 1

    cdef Mob *mobs_map[GRID_SIZE]
    for e in range(GRID_SIZE):
        mobs_map[e] = &empty_mob

    for e in range(mobs_len):
        cur_mob = &mobs[e]
        mobs_map[cur_mob.pos] = cur_mob

    # print_grid(grid, GRID_W, step=0)  # TEMP

    # for cur_mob in mobs:
    #     if cur_mob.type > 0:
    #         print(f"Mob{{type={cur_mob.type}, hp={cur_mob.hp}, pos={cur_mob.pos}}}")

    # === Fight while there are elves and goblins left ===
    cdef int nb_rounds = 0
    while type_count[3] > 0 and type_count[4] > 0:

        # === New turn: reset played
        for cur_mob in mobs:
            cur_mob.played = False

        # === Search for Mob in whole grid (reading order) ===
        for i in range(GRID_SIZE):
            e = grid[i]
            if e != 3 and e != 4:
                continue

            cur_mob = mobs_map[i]
            if cur_mob.played:
                continue

            # --- It is the turn of the cur_mob Mob ---
            opp_type = 3 if cur_mob.type == 4 else 4
            cur_mob.played = True

            # --- Check if opponent in range ---
            min_hp = HP_INF
            for r in around:
                cur_tst = mobs_map[i + r]
                if cur_tst.type == opp_type and cur_tst.hp < min_hp:
                    cur_opp = cur_tst
                    min_hp = cur_opp.hp

            if min_hp < HP_INF:
                # --- Found one opponent in range ---

                # -- Hit the opponent --
                cur_opp.hp -= min(3, cur_opp.hp)

                # -- Killed? --
                if cur_opp.hp <= 0:
                    mobs_map[cur_opp.pos] = &empty_mob  # R
                    grid[cur_opp.pos] = 2               # I
                    type_count[cur_opp.type] -= 1       # P
                    cur_opp.type = 0
                    cur_opp.pos = 0

            else:
                # --- No opponent in range ---

                # -- Recompute all distances from cur_mob ---
                for j in range(GRID_SIZE):
                    dist[j] = DIST_INF
                dist[i] = 0

                for r in around:
                    if grid[i + r] == 2:
                        fill_distances(grid, dist, i + r)

                # print_dist(dist, GRID_W)  # TEMP
                # return 0  # TEMP

                # -- Search for the closest spot next to an opponent ---
                min_dist = DIST_INF
                min_pos = DIST_INF
                found_opp = False
                for cur_tst in mobs:
                    if cur_tst.type == opp_type:
                        found_opp = True
                        for r in around:
                            if grid[cur_tst.pos + r] == 2 \
                                    and dist[cur_tst.pos + r] < min_dist \
                                    or dist[cur_tst.pos + r] == min_dist and min_dist < DIST_INF and cur_tst.pos + r < min_pos:
                                min_dist = dist[cur_tst.pos + r]
                                min_pos = cur_tst.pos + r
                                cur_opp = cur_tst

                if not found_opp:
                    break

                # -- If no accessible opponent, end turn
                if min_pos == DIST_INF:
                    continue

                # -- Accessible opponent, take a step
                # print(f"{i} going towards: Mob{{type={cur_opp.type}, hp={cur_opp.hp}, pos={cur_opp.pos}}}")

                # steps = 0  # TEMP

                mov_pos = min_pos
                while dist[mov_pos] > 1:
                    # # <<<
                    # steps += 1
                    # if steps > 500:
                    #     print_dist(dist, GRID_W)  # TEMP
                    #     print(f"Could not find a way from {min_pos} to {i}")
                    #     return 1
                    # # >>>

                    for r in around:
                        if dist[mov_pos + r] < dist[mov_pos]:
                            # print(f"Step: {mov_pos} -> {mov_pos + r}")
                            mov_pos = mov_pos + r
                            break

                # -- Step from cur_mob.pos to mov_pos --
                # print(f"Step: {cur_mob.pos} -> {mov_pos}")
                grid[cur_mob.pos] = 2
                grid[mov_pos] = cur_mob.type
                mobs_map[cur_mob.pos] = &empty_mob
                mobs_map[mov_pos] = cur_mob

                cur_mob.pos = mov_pos

                # == Attack ==
                # --- Check if opponent in range ---
                min_hp = HP_INF
                for r in around:
                    cur_tst = mobs_map[mov_pos + r]
                    if cur_tst.type == opp_type and cur_tst.hp < min_hp:
                        cur_opp = cur_tst
                        min_hp = cur_opp.hp

                if min_hp < HP_INF:
                    # --- Found one opponent in range ---

                    # -- Hit the opponent --
                    cur_opp.hp -= min(3, cur_opp.hp)

                    # -- Killed? --
                    if cur_opp.hp <= 0:
                        mobs_map[cur_opp.pos] = &empty_mob  # R
                        grid[cur_opp.pos] = 2               # I
                        type_count[cur_opp.type] -= 1       # P
                        cur_opp.type = 0
                        cur_opp.pos = 0
                # == Attack end ==

                # break  # TEMP

        # print(f"End of turn {nb_rounds}")  # TEMP
        # print_grid(grid, GRID_W)  # TEMP
        # print_grid_hp(grid, mobs, GRID_W, step=nb_rounds)  # TEMP
        # break  # TEMP

        if not found_opp:
            break

        nb_rounds += 1

        # if nb_rounds > 10000:
        #     break

    # for cur_mob in mobs:
    #     if cur_mob.type > 0:
    #         print(f"Mob{{type={cur_mob.type}, hp={cur_mob.hp}, pos={cur_mob.pos}}}")

    cdef int hp_sum = 0
    for cur_mob in mobs:
        if cur_mob.type > 0:
            hp_sum += cur_mob.hp

    print(nb_rounds, "rounds")
    print(hp_sum, "hp")
    print(nb_rounds * hp_sum, "total\n")

    return nb_rounds * hp_sum
