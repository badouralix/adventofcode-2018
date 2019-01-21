# def make_tree(data, start):
#     nbc = data[start]
#     nbm = data[start + 1]
#     children = []
#     children_cur = start + 2
#     for c in range(nbc):
#         child, children_cur = make_tree(data, children_cur)
#         children.append(child)
#     metadata = [data[children_cur + m] for m in range(nbm)]
#     return (nbc, nbm, children, metadata), children_cur + nbm

# def sum_metadata(tree):
#     return sum(tree[3]) + sum(sum_metadata(child) for child in tree[2])


def make_tree_sum_metadata(data, start):
    nbm = data[start + 1]
    children_cur = start + 2
    children_sum = 0
    for c in range(data[start]):
        child, children_cur = make_tree_sum_metadata(data, children_cur)
        children_sum += child
    return children_sum + sum(data[children_cur : children_cur + nbm]), children_cur + nbm


cpdef int run(s):
    # cdef unsigned char _data[25000]
    # cdef int i

    # for i, d in enumerate(s.split(" ")):
    #     _data[i] = int(d)

    # print(data[0], data[1], data[2], data[3], data[4])

    _data = [int(x) for x in s.split(" ")]

    # _tree, _ = make_tree(_data, 0)
    # return sum_metadata(_tree)

    return make_tree_sum_metadata(_data, 0)[0]
