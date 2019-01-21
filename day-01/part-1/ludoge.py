from tool.runners.python import SubmissionPy


class LudogeSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        return sum((int(line) for line in s.splitlines()))
