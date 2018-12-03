from collections import Counter
from runners.python import SubmissionPy

class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        lines = s.splitlines()
        twice = three_times = 0
        for row in lines:
            c = Counter(row)
            if 2 in c.values():
                twice += 1
            elif 3 in c.values():
                three_times += 1
        return twice * three_times
