def make_tree(data, start):
    nbc = data[start]
    nbm = data[start + 1]
    children_cur = start + 2
    children = []
    for c in range(nbc):
        child, children_cur = make_tree(data, children_cur)
        children.append(child)
    metadata = data[children_cur : children_cur + nbm]
    return (nbc, nbm, children, metadata), children_cur + nbm


cdef int value(tree):
    cdef int nbc = tree[0]
    cdef int m
    if nbc == 0:
        return sum(tree[3])
    cdef int count = 0
    for m in tree[3]:
        if 0 <= m - 1 < nbc:
            count += value(tree[2][m - 1])
    return count


cpdef int run(s):
    # cdef unsigned char _data[25000]
    # cdef int i

    # for i, d in enumerate(s.split(" ")):
    #     _data[i] = int(d)

    _data = [int(x) for x in s.split(" ")]

    _tree, _ = make_tree(_data, 0)
    return value(_tree)
