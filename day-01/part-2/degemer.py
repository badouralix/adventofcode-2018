from runners.python import SubmissionPy
import itertools


class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        res = 0
        known = {}
        for change in itertools.cycle(s.splitlines()):
            if res in known:
                return res
            known[res] = True
            res += eval(change)
