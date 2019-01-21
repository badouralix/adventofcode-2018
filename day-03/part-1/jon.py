from tool.runners.python import SubmissionPy


class JonSubmission(SubmissionPy):

    def run(self, s):
        claimed = dict()

        for l in s.splitlines():
            a = l.split('@')[1].strip().split(':')
            b = a[0].split(',')
            c = a[1].split('x')
            x = int(b[0])
            y = int(b[1])
            w = int(c[0])
            h = int(c[1])

            for i in range(w):
                for j in range(h):
                    pt = (x+i, y+j)
                    claimed[pt] = claimed.get(pt, 0) + 1

        return sum(1 for v in claimed.values() if v > 1)

