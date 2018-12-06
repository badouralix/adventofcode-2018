from runners.python import SubmissionPy


class BebertSubmission(SubmissionPy):

    def run(self, s):
        min_length = 1000000000
        for rem in range(65, 91):
            letters = [c for c in s if ord(c) != rem and ord(c) != rem + 32]
            cur = 0
            while cur < len(letters) - 1:
                if abs(ord(letters[cur]) - ord(letters[cur + 1])) == 32:
                    del letters[cur]
                    del letters[cur]
                    if cur > 0:
                        cur -= 1
                else:
                    cur += 1
            if len(letters) < min_length:
                min_length = len(letters)
        return min_length
