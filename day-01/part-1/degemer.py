from runners.python import SubmissionPy


class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        res = 0
        for change in s.splitlines():
            res += eval(change)
        return res
