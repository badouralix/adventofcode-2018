import sys
from collections import Counter

class Submission():

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        lines = s.splitlines()
        twice = three_times = 0
        for row in lines:
            c = Counter(row)
            if 2 in c.values():
                twice += 1
            if 3 in c.values():
                three_times += 1
        return twice * three_times

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
