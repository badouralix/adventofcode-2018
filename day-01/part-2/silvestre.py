import sys
import numpy as np

class Submission():

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

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
