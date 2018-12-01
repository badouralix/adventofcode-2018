from runners.python import SubmissionPy


class JonSubmission(SubmissionPy):

    def run(self, s):
        return eval(s.replace("\n", ""))
