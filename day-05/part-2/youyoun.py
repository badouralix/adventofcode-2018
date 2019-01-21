from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        polymer_lengths = {}
        for i in range(65, 91):
            polymer = s.replace(chr(i), "").replace(chr(i+32), "")
            str_ = []
            for c in polymer:
                if str_ and abs(ord(c) - ord(str_[-1])) == 32:
                    str_.pop()
                else:
                    str_.append(c)
            polymer_lengths[i] = len(str_)
        return min(polymer_lengths.values())
