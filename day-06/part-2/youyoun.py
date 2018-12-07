from runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        points = [[int(e.strip()) for e in x.split(",")] for x in s.splitlines()]
        if len(points) < 10:
            limit = 32
        else:
            limit = 10000
        w, h = max((p[0] for p in points)), max((p[1] for p in points))
        count = 0
        for i in range(h + 1):
            for j in range(w + 1):
                distances = {}
                for k, e in enumerate(points):
                    dist = abs(i - e[0]) + abs(j - e[1])
                    distances[k] = dist
                if sum(distances.values()) < limit:
                    count += 1
        return count
