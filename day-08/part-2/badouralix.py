from runners.python import SubmissionPy


class BadouralixSubmission(SubmissionPy):

    def run(self, s):
        split = list(map(int, s.split(" ")))
        _, r = self.rec(split)
        return r

    def rec(self, ll):
        nodes = ll[0]
        metadata = ll[1]
        ll = ll[2:]

        if nodes == 0:
            return ll[metadata:], sum(ll[:metadata])

        li = list()
        result = 0
        for n in range(nodes):
            ll, nli = self.rec(ll)
            li.append(nli)
        for i in range(metadata):
            if ll[i] <= nodes:
                result += li[ll[i] - 1]
        return ll[metadata:], result
