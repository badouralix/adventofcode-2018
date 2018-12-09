from tool.runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        arr = list(map(int, s.splitlines()[0].split()))

        def score_node(arr, i_node):
            n_child = arr[i_node]
            n_meta = arr[i_node + 1]
            i_next = i_node + 2
            if n_child == 0:
                return i_next + n_meta, sum(arr[i_next:i_next+n_meta])
            else:
                score_children = []
                for _ in range(n_child):
                    i_next, tmp = score_node(arr, i_next)
                    score_children.append(tmp)
            return i_next + n_meta, sum(score_children[meta-1] for meta in arr[i_next:i_next+n_meta] if 0 <= meta - 1 < len(score_children))

        return score_node(arr, 0)[1]
