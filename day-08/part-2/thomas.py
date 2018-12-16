from tool.runners.python import SubmissionPy


def process(tree, i_node):
    child_values = []
    node_value = 0
    nb_child, nb_meta = tree[i_node : i_node + 2]
    end = i_node + 1

    for i in range(nb_child):
        value, end = process(tree, end + 1)
        child_values.append(value)

    if nb_child != 0:
        for i in range(end + 1, end + nb_meta + 1):
            if tree[i] > 0 and tree[i] <= nb_child:
                node_value += child_values[tree[i] - 1]
    else:
        node_value = sum(tree[i] for i in range(end + 1, end + nb_meta + 1))
    return node_value, end + nb_meta


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        return process([int(x) for x in s.split()], 0)[0]
