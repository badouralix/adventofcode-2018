from runners.python import SubmissionPy

from itertools import combinations


class MathieuSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here


        def sim(box_1, box_2):
            count = 0
            for a, b in zip(box_1, box_2):
                if a != b:
                    count += 1
            return count


        def common_letters(box_1, box_2):
            res = ""
            for a, b in zip(box_1, box_2):
                if a == b:
                    res += a

            return res

        lines = s.split('\n')
        for box_1, box_2 in combinations(lines, 2):
            if sim(box_1, box_2) == 1:
                return common_letters(box_1, box_2)
