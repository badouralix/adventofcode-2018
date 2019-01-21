from tool.runners.python import SubmissionPy


class MathieuSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        return sum(map(int, s.split('\n')))
