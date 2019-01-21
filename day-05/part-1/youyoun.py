from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        str_ = []
        for c in s:
            if str_ and abs(ord(c) - ord(str_[-1])) == 32:
                str_.pop()
            else:
                str_.append(c)
        return len(str_)
