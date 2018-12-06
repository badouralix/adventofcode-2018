from runners.python import SubmissionPy
import re


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        points = {}
        ids = set({})
        for e in s.splitlines():
            params = re.search("#(\d+)\s@\s(\d+),(\d+):\s(\d+)x(\d+)", e)
            id_, x, y, l, h = params.group(1), int(params.group(2)), int(params.group(3)), int(params.group(4)), int(
                params.group(5))
            ids.add(id_)
            for i in range(l):
                removed = False
                for j in range(h):
                    p = (x + i, y + j)
                    if p not in points:
                        points[p] = [id_]
                    else:
                        points[p].append(id_)
                        if not removed:
                            for id2_ in points[p]:
                                if id2_ in ids:
                                    ids.remove(id2_)
                            removed = True
        for coords, ids_ in points.items():
            if len(ids_) > 1:
                for id_ in ids_:
                    if id_ in ids:
                        ids.remove(id_)
        return ids.pop()
