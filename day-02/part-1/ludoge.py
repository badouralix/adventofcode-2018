import sys
from collections import Counter

class Submission():

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        sums = [sum(x) for x in zip(*self.count(s))]
        return sums[0]*sums[1]

    def count(self, s):
        for line in s.splitlines():
            counter = Counter(line)
            y1 = 1 if [c for c in counter if counter[c] == 2] else 0
            y2 = 1 if [c for c in counter if counter[c] == 3] else 0
            yield (y1, y2)

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
