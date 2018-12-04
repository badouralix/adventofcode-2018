import sys
from collections import Counter


class Submission():

    def run(self, s: str):
        twos = 0
        threes = 0
        for line in s.splitlines():
            count = Counter(line.strip())
            if 2 in count.values():
                twos += 1
            if 3 in count.values():
                threes += 1
        return twos * threes

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
