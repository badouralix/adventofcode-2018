from runners.python import SubmissionPy


class ThomasSubmission(SubmissionPy):

    def run(self, s):
        l = s.split('\n')
        for x in l:
            for y in l:
                tmp = self.compare_words(x, y)
                if tmp:
                    return tmp

    @staticmethod
    def compare_words(x, y):
        diffletter = None
        for i in range(len(x)):
            if x[i] != y[i]:
                if diffletter is not None:
                    return False
                diffletter = i
        if diffletter is not None:
            return ''.join([x[i] for i in range(len(x)) if i != diffletter])
        return False
