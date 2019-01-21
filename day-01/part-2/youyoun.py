from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        passed_freqs = {0}
        freqs = [int(x) for x in s.splitlines()]
        score = 0
        while True:
            for f in freqs:
                score += f
                if score in passed_freqs:
                    return score
                passed_freqs.add(score)
