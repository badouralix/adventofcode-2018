from runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        lines = s.splitlines()
        lines.sort()
        rev = sorted(lines, key=lambda x: x[::-1])
        
        for lst in (lines, rev):
            for i, row1 in enumerate(lst[:-1]):
                row2 = lst[i+1]
                diff = [x!=y for x, y in zip(row1, row2)]
                if sum(diff) == 1:
                    return "".join([el for el, b in zip(row1, diff) if not b])
        print("Silvestre failed.")
