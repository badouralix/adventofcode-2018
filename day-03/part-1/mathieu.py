from tool.runners.python import SubmissionPy

import re

class MathieuSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        overlapping = set()
        claimed = set()
        for line in s.split('\n'):
            #id = int(re.search(r'#(\d+)', line).group(1))
            x = int(re.search(r'@ (\d+),', line).group(1))
            y = int(re.search(r',(\d+):', line).group(1))
            w = int(re.search(r': (\d+)x', line).group(1))
            h = int(re.search(r'x(\d+)$', line).group(1))
            cur_claimed = set((i + x, y + j) for i in range(w) for j in range(h))
            overlapping |= cur_claimed & claimed
            claimed |= cur_claimed

        return len(overlapping)
