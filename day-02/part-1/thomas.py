import sys
from collections import Counter


class Submission():

    def run(self, s):
        two = 0
        three = 0

        for word in s.split('\n'):
            letters = Counter(word)
            two += 2 in letters.values()
            three += 3 in letters.values()

        return two * three

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
