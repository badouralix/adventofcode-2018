from runners.python import SubmissionPy


class LudogeSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here

        freqs = {0}
        new_freq = 0
        for delta in self.ad_nauseam(s):
            new_freq += delta
            if new_freq in freqs:
                return new_freq
            else:
                freqs.add(new_freq)

    def ad_nauseam(self, s):
        while True:
            for line in s.splitlines():
                yield int(line)