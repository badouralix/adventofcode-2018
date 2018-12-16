
from tool.runners.python import SubmissionPy
class RonanSubmission(SubmissionPy):
    @staticmethod
    def run(input):
        sum = 0
        seen = set([sum])
        freqs = [int(x) for x in input.split("\n")]
        while 1:
            for n in freqs:
                sum += int(n)
                if sum in seen:
                    return sum
                seen.add(sum)