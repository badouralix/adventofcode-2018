from runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        arr = list(map(int, s.splitlines()[0].split()))

        def sum_meta(arr, i_node):
            n_child = arr[i_node]
            n_meta = arr[i_node + 1]
            i_next = i_node + 2
            ret = 0
            for _ in range(n_child):
                i_next, tmp = sum_meta(arr, i_next)
                ret += tmp
            return i_next + n_meta, ret + sum(arr[i_next:i_next+n_meta])

        return sum_meta(arr, 0)[1]
