from runners.python import SubmissionPy


class ThomasSubmission(SubmissionPy):

    def run(self, s):
        freqs = set([0])
        freq = 0
        l = s.split('\n')
        while True:
            for i in l:
                freq += int(i)
                if freq in freqs:
                    return freq
                freqs.add(freq)
