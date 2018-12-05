from tool.runners.python import SubmissionPy
import numpy as np


class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        claim = np.empty((1000, 1000), dtype=np.int)
        claim[:] = 0

        for case in s.splitlines():
            _, t = case.split("@")
            tops, sizes = t.split(':')
            left, top = map(lambda x: int(x.strip()), tops.split(','))
            width, height = map(lambda x: int(x.strip()), sizes.split('x'))
            claim[left:left + width, top:top + height] += 1

        claim[claim <= 1] = 0
        claim[claim >= 2] = 1
        return np.sum(claim)
