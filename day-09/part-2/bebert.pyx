from cpython cimport array
import array
import cython


# def marble_repr(cur_marble, lefts, rights, sel=False):
#     # r = f"{lefts[cur_marble]:2d}_{cur_marble:2d}_{rights[cur_marble]:2d}"
#     r = f"{cur_marble:2d}"
#     return f"({r})" if sel else f" {r} "


# def print_marbles(cur_marble, lefts, rights, cur_player, start):
#     cdef int i, old_value
#     cdef int sel_value = cur_marble
#     cur_marble = start
#
#     res = f"[{cur_player:3d}] "
#     res += marble_repr(cur_marble, lefts, rights, sel=cur_marble == sel_value)
#
#     i = 0
#     while rights[cur_marble] != start:
#         # i += 1
#         # if i > 10:
#         #     break
#         cur_marble = rights[cur_marble]
#         res += marble_repr(cur_marble, lefts, rights, sel=cur_marble == sel_value)
#     print(res)


@cython.cdivision(True)
cpdef long run(s):
    cdef int num_players = int(s.split(" ", 1)[0])
    cdef int max_points = int(s.rsplit(" ", 2)[1])
    # num_players = 9
    # max_points = 25

    max_points *= 100
    # print(f"Num players: {num_players}, Max points: {max_points}")

    cdef array.array rights = array.array('i', [-1] * (max_points + 2))
    cdef array.array lefts =  array.array('i', [-1] * (max_points + 2))

    rights.data.as_ints[0] = 0
    lefts.data.as_ints[0] = 0

    cdef long scores[1000]
    for i in range(1000):
        scores[i] = 0

    cdef int cur_player = 0
    cdef int cur_marble = 0
    cdef int left_marble, right_marble

    cdef int cur_num = 0
    cdef int k

    while cur_num <= max_points:
        cur_num += 1

        # print_marbles(cur_marble, lefts, rights, cur_player, 0)

        cur_player = cur_player % num_players + 1

        if cur_num % 23 == 0:
            scores[cur_player] += cur_num

            for k in range(7):
                cur_marble = lefts.data.as_ints[cur_marble]
            scores[cur_player] += cur_marble

            left_marble = lefts.data.as_ints[cur_marble]
            right_marble = rights.data.as_ints[cur_marble]
            rights.data.as_ints[left_marble] = right_marble
            lefts.data.as_ints[right_marble] = left_marble

            lefts.data.as_ints[cur_marble] = -1
            rights.data.as_ints[cur_marble] = -1
            cur_marble = right_marble

        else:
            left_marble = rights.data.as_ints[cur_marble]
            right_marble = rights.data.as_ints[rights.data.as_ints[cur_marble]]

            cur_marble = cur_num

            lefts.data.as_ints[cur_marble] = left_marble
            rights.data.as_ints[cur_marble] = right_marble

            lefts.data.as_ints[right_marble] = cur_marble
            rights.data.as_ints[left_marble] = cur_marble

    return max(scores)
