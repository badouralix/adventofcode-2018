from tool.runners.python import SubmissionPy


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        tree = [int(x) for x in s.split()]
        nb_nodes = []
        nb_metadata = [0]
        i = 0
        sum_metadata = 0
        while i < len(tree):
            if not len(nb_nodes) or nb_nodes[-1]:
                nb_nodes.append(tree[i])
                nb_metadata.append(tree[i + 1])
                i += 2
            else:
                sum_metadata += sum([tree[i + j] for j in range(nb_metadata[-1])])
                i += nb_metadata[-1]
                nb_metadata.pop()
                nb_nodes.pop()
                if len(nb_nodes):
                    nb_nodes[-1] -= 1
        return sum_metadata
