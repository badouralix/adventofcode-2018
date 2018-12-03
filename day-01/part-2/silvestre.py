from runners.python import SubmissionPy
import numpy as np

class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        array = np.fromstring(s, dtype=np.int64, sep="\n")
        reached = set()
        curr = loop = 0
        while loop < 1000:
            for el in array:
                if curr in reached:
                    return curr
                else:
                    reached.add(curr)
                    curr += el
        print('Error: Never reached the same frequency twice')
