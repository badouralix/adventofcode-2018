from runners.python import SubmissionPy
class RonanSubmission(SubmissionPy):
    @staticmethod
    def run(input):
        return sum([
            int(n)
            for n in input.split('\n')
        ])
