import sys
import numpy as np


class Submission():

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        array = np.fromstring(s, dtype=np.int64, sep="\n")
        return array.sum()

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
