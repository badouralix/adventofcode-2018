from runners.python import SubmissionPy


class JonSubmission(SubmissionPy):

    def run(self, s):

        l = [x.strip() for x in s.splitlines()]

        for i in range(len(l)):
            for j in range(i+1, len(l)):
                if hamming(l[i], l[j]) == 1:
                    return "".join(l[i][k] for k in range(len(l[i])) if l[i][k] == l[j][k])


def hamming(a, b):
    return sum(1 for i in range(len(a)) if a[i] != b[i])
