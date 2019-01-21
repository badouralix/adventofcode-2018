from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        score = 0
        for e in (int(x) for x in s.splitlines()):
            score += e
        return score
