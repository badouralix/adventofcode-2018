cpdef run(s):
    cdef int min_length = 1000000000
    cdef int rem
    for rem in range(65, 91):
        res = []
        for x in s:
            if ord(x) == rem or ord(x) == rem + 32:
                continue
            if res and abs(ord(res[-1]) - ord(x)) == 32:
                res.pop()
            else:
                res.append(x)
        if len(res) < min_length:
            min_length = len(res)
    return min_length
