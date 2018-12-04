import sys
from collections import Counter

class Submission():

    def run(self, s):

        c2 = 0
        c3 = 0

        for l in s.splitlines():
            c = Counter(l.strip())
            if 2 in c.values():
                c2 += 1
            if 3 in c.values():
                c3 += 1

        return c2 * c3

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
