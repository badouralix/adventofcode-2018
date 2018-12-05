from runners.python import SubmissionPy


class MathieuSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        seen = {0}
        freq = 0
        numbers = list(map(int, s.split('\n')))
        while True:
            for num in numbers:
                freq += num
                if freq in seen: return freq
                seen.add(freq)
