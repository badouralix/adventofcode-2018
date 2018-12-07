from runners.python import SubmissionPy
import re


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        score = 0
        points = {}
        for e in s.splitlines():
            params = re.search("#(\d+)\s@\s(\d+),(\d+):\s(\d+)x(\d+)", e)
            x, y, l, h = int(params.group(2)), int(params.group(3)), int(params.group(4)), int(params.group(5))
            for i in range(l):
                for j in range(h):
                    p = (i + x, j + y)
                    if p not in points:
                        points[p] = 1
                    else:
                        points[p] += 1
        for coords, times in points.items():
            if times > 1:
                score += 1
        return score
