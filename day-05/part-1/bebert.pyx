cpdef int run(s):
    res = []
    for x in s:
        if res and abs(ord(res[-1]) - ord(x)) == 32:
            res.pop()
        else:
            res.append(x)
    return len(res)
