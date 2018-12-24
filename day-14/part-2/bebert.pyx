from cpython cimport array
import array
import cython


@cython.cdivision(True)
cpdef int run(s):
    cdef int i, j, to_add
    cdef bint searching = True
    cdef int sel_sum

    cdef int search_for[10]
    cdef int search_for_len = 0
    for x in s.strip():
        search_for[search_for_len] = int(x)
        search_for_len += 1

    cdef array.array scores = array.array('i', [3, 7])
    cdef int score_len = 2

    cdef int sel0 = 0
    cdef int sel1 = 1

    while searching:
        sel_sum = scores.data.as_ints[sel0] + scores.data.as_ints[sel1]
        if sel_sum < 10:
            to_add = 1
            array.resize_smart(scores, score_len + 1)
            scores.data.as_ints[score_len] = sel_sum
        else:
            to_add = 2
            array.resize_smart(scores, score_len + 2)
            scores.data.as_ints[score_len] = sel_sum // 10
            scores.data.as_ints[score_len + 1] = sel_sum % 10
        score_len += to_add

        if score_len > search_for_len:
            if to_add == 2:
                for i in range(search_for_len):
                    if scores.data.as_ints[score_len - search_for_len + i - 1] != search_for[i]:
                        break
                else:
                    return score_len - search_for_len - 1

            for i in range(search_for_len):
                if scores.data.as_ints[score_len - search_for_len + i] != search_for[i]:
                    break
            else:
                return score_len - search_for_len

        sel0 = (sel0 + scores.data.as_ints[sel0] + 1) % score_len
        sel1 = (sel1 + scores.data.as_ints[sel1] + 1) % score_len
