from runners.python import SubmissionPy


class BadouralixSubmission(SubmissionPy):

    def run(self, s):
        split = list(map(int, s.split(" ")))
        _, acc = self.rec(split, 0)
        return acc

    def rec(self, ll, acc):
        nodes = ll[0]
        metadata = ll[1]
        ll = ll[2:]
        for n in range(nodes):
            ll, acc = self.rec(ll, acc)
        for i in range(metadata):
            acc += ll[i]
        return ll[metadata:], acc
