from tool.runners.python import SubmissionPy
import collections

class JonSubmission(SubmissionPy):

    def run(self, s):
        l = [int(x) for x in s.split("\n")]
        d = {0}
        s = 0
        for i in range(100000000): # eh oui
            s += l[i%len(l)]
            if s in d:
                return s
            d.add(s)
