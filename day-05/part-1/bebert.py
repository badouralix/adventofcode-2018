from runners.python import SubmissionPy


class BebertSubmission(SubmissionPy):

    def run(self, s):
        letters = list(s)
        cur = 0
        while cur < len(letters) - 1:
            if abs(ord(letters[cur]) - ord(letters[cur + 1])) == 32:
                del letters[cur]
                del letters[cur]
                if cur > 0:
                    cur -= 1
            else:
                cur += 1
        return len(letters)
