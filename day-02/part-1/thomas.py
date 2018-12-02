from runners.python import SubmissionPy
from collections import Counter


class ThomasSubmission(SubmissionPy):

    def run(self, s):
        two = 0
        three = 0

        for word in s.split('\n'):
            letters = Counter(word)
            two += 2 in letters.values()
            three += 3 in letters.values()

        return two * three
