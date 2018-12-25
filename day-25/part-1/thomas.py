from tool.runners.python import SubmissionPy
from collections import defaultdict


def parse_point(s):
    return tuple([int(n) for n in s.split(",")])


def manhattan(p1, p2):
    return sum([abs(p1[i] - p2[i]) for i in range(len(p1))])


class UnionFind:
    def __init__(self, n):
        self.parents = [None] * n
        self.rank = [1] * n
        self.nb_sets = n

    def find(self, i):
        if self.parents[i] is not None:
            p = self.find(self.parents[i])
            self.parents[i] = p
            return p
        return i

    def union(self, i, j):
        i_root = self.find(i)
        j_root = self.find(j)
        if i_root != j_root:
            self.nb_sets -= 1
            if self.rank[i_root] < self.rank[j_root]:
                self.parents[i_root] = j_root
            else:
                self.parents[j_root] = i_root
                if self.rank[i_root] == self.rank[j_root]:
                    self.rank[i_root] += 1


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        points = []
        for point in s.splitlines():
            points.append(parse_point(point))

        uf = UnionFind(len(points))

        for i, point in enumerate(points):
            for j, npoint in enumerate(points):
                if manhattan(point, npoint) <= 3:
                    uf.union(i, j)

        return uf.nb_sets
