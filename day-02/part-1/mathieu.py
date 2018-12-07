from runners.python import SubmissionPy

from collections import Counter

class MathieuSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        lines = s.split('\n')
        count_twice = 0
        count_three = 0
        for line in lines:
            counter = Counter(line)
            if 2 in counter.values():
                count_twice += 1
            if 3 in counter.values():
                count_three += 1

        return count_three * count_twice
