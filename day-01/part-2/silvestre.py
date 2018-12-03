from runners.python import SubmissionPy
import numpy as np

class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        array = np.fromstring(s, dtype=np.int64, sep="\n")
        reached = set()
        curr = 0
        i = 0
        while True:
            if curr in reached or i > 150000: # Security
                return curr
            else:
                reached.add(curr)
                curr += array[i%array.size]
                i += 1
        return 0
