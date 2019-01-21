import string
from collections import deque
from tool.runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def collapse(self, s):
        ret = deque()
        for el1 in s:
            el2 = ret[-1] if ret else ""
            if el1 != el2 and el1.lower() == el2.lower():
                ret.pop()
            else:
                ret.append(el1)
        return "".join(ret)

    def run(self, s):
        s = self.collapse(s)
        letters = string.ascii_lowercase
        lenghts = (len(self.collapse(s.replace(let, '').replace(let.upper(), ''))) for let in letters)
        return min(lenghts)
