from runners.python import SubmissionPy

class ThomasSubmission(SubmissionPy):

    @staticmethod
    def react(s):
        res = []
        for char in s:
            if len(res) > 0 and abs(ord(char) - ord(res[-1])) == 32:
                res.pop()
            else:
                res.append(char)
        return len(res)

    def run(self, s):
        return min([self.react(s.replace(chr(i), '').replace(chr(i+32), '')) for i in range(65, 91)])
