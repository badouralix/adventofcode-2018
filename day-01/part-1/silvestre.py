from runners.python import SubmissionPy

import numpy as np


class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        array = np.fromstring(s, dtype=np.int64, sep="\n")
        return array.sum()
