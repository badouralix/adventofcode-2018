from runners.python import SubmissionPy
import numpy as np


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        points = [[int(e.strip()) for e in x.split(",")] for x in s.splitlines()]
        w, h = max((p[0] for p in points)), max((p[1] for p in points))
        plan = np.zeros((h + 1, w + 1))
        for i, e in enumerate(points):
            plan[e[1], e[0]] = i + 1
        borders_points = {-1}
        for i in range(plan.shape[0]):
            for j in range(plan.shape[1]):
                distances = {}
                for k, e in enumerate(points):
                    dist = abs(i - e[0]) + abs(j - e[1])
                    distances[k] = dist
                min_dist = min(distances.values())
                close_points = {point for point, dist in distances.items() if dist == min_dist}
                if len(close_points) >= 2:
                    plan[i, j] = -1
                else:
                    point = close_points.pop()
                    plan[i, j] = point + 1
                    if i == 0 or i == plan.shape[1] or j == 0 or j == plan.shape[0]:
                        borders_points.add(point + 1)
        unique, counts = np.unique(plan, return_counts=True)
        point_counts = dict(zip(unique, counts))
        return max([c for p, c in point_counts.items() if p not in borders_points])