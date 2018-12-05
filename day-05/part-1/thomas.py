from runners.python import SubmissionPy
import re


class ThomasSubmission(SubmissionPy):

    def run(self, s):
        res = []
        for char in s:
            if len(res) > 0 and abs(ord(char) - ord(res[-1])) == 32:
                res.pop()
            else:
                res.append(char)
        return len(res)
