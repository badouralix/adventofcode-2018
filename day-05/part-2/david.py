from runners.python import SubmissionPy


class DavidSubmission(SubmissionPy):

    def aux(self, s):
        n = len(s)
        i = 0
        while i < len(s)-1:
            if s[i].lower() == s[i+1].lower() and s[i] != s[i+1]:
                s = s[:i] + s[i+2:]
                if i > 0:
                    i -= 1
                continue

            i += 1

        return len(s)

    def run(self, s):
        shortest_length = None
        for c in "abcdefghijklmnopqrstuvwxyz":
            s0 = "".join(x for x in s if x.lower() != c)
            length = self.aux(s0)
            if shortest_length is None or length < shortest_length:
                shortest_length = length
        return shortest_length
