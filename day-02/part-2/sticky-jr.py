from tool.runners.python import SubmissionPy


class StickySubmission(SubmissionPy):

    def run(self, s):
        lines = s.splitlines()
        lines.sort()
        rev = sorted(lines, key=lambda x: x[::-1])
        
        for lst in (lines, rev):
            for i, row1 in enumerate(lst[:-1]):
                row2 = lst[i+1]
                out = ''.join([x for x, y in zip(row1, row2) if x==y])
                if len(out) == len(row1) - 1:
                    return out
