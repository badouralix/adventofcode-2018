from tool.runners.python import SubmissionPy


class BebertSubmission(SubmissionPy):

    def run(self, s: str):
        lines = [l.strip() for l in s.splitlines()]
        for i, line1 in enumerate(lines):
            for line2 in lines[i+1:]:
                diff = 0
                for x, y in zip(line1, line2):
                    if x != y:
                        diff += 1
                        if diff > 1:
                            break
                if diff == 1:
                    return "".join(x for x, y in zip(line1.strip(), line2.strip()) if x == y)
