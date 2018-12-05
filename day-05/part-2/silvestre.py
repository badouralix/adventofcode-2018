import string
from collections import deque
from runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def collapse(self, s):
        # condition empruntée à Thomas, voir part 1 pour ma condition
        ret = deque()
        for el1 in s:
            if ret and abs(ord(el1) - ord(ret[-1])) == 32: 
                ret.pop()
            else:
                ret.append(el1)
        return "".join(ret)

    def run(self, s):
        s = self.collapse(s)
        letters = string.ascii_lowercase
        lenghts = (len(self.collapse(s.replace(let, '').replace(let.upper(), ''))) for let in letters)
        return min(lenghts)
