import sys
import itertools


class Submission():

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

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
