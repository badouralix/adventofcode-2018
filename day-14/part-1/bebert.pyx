import cython

DEF MAX_LEN = 1000000

@cython.cdivision(True)
cpdef str run(s):
    cdef int i
    cdef unsigned char sel_sum

    cdef int tries = int(s)

    cdef unsigned char scores[MAX_LEN]
    scores[0] = 3
    scores[1] = 7
    cdef int score_len = 2

    cdef int sel0 = 0
    cdef int sel1 = 1

    while score_len < tries + 10:
        sel_sum = scores[sel0] + scores[sel1]
        if sel_sum < 10:
            scores[score_len] = sel_sum
            score_len += 1
        else:
            scores[score_len] = sel_sum // 10
            scores[score_len + 1] = sel_sum % 10
            score_len += 2
        sel0 = (sel0 + scores[sel0] + 1) % score_len
        sel1 = (sel1 + scores[sel1] + 1) % score_len

    res = ["-"] * 10
    for i in range(10):
        res[i] = str(scores[tries+i])
    return "".join(res)
