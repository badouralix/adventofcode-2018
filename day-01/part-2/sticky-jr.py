from runners.python import SubmissionPy

class StickySubmission(SubmissionPy):

    def run(self, s):
        l = s.split('\n')
        L = len(l)
        d = [0]
        s = i = 0
        while True:
            s += int(l[i%L])
            if s in d:
                return s
            d.append(s)
            i += 1
