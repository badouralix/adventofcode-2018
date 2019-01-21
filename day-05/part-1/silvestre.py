from collections import deque
from tool.runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        ret = deque()
        for el1 in s:
            el2 = ret[-1] if ret else ""
            if el1 != el2 and el1.lower() == el2.lower():
                ret.pop()
            else:
                ret.append(el1)
        return len(ret)
