from runners.python import SubmissionPy

class ThomasSubmission(SubmissionPy):

    def run(self, s):
        return sum([int(i) for i in s.split('\n')])
