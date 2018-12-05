from collections import deque
from runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        s = s.splitlines()[0]
        ret = deque()
        for el1 in s:
            el2 = ret[-1] if ret else ""
            if ret and el1.islower() != el2.islower() and el1.lower() == el2.lower():
                ret.pop()
            else:
                ret.append(el1)
        return len(ret)
