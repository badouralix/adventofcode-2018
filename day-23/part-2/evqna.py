from tool.runners.python import SubmissionPy

from collections import defaultdict
from dataclasses import dataclass
from itertools import combinations
from re import findall
from typing import Dict, List, Set


@dataclass
class Robot:
    x: int
    y: int
    z: int
    radius: int

def d(r1: Robot, r2: Robot):
    return abs(r1.x - r2.x) + abs(r1.y - r2.y) + abs(r1.z - r2.z)

def ranges_intersect(r1: Robot, r2: Robot):
    return d(r1, r2) <= r1.radius + r2.radius

# Parse input

def parse_robots(s) -> List[Robot]:
    robots = []
    for l in s.splitlines():
        x, y, z, r = [int(c) for c in findall(r'-?\d+', l)]
        robots.append(Robot(x, y, z, r))
    return robots


# Graph functions

def build_overlap_graph(R: List[Robot]) -> Dict[int, Set[int]]:
    G = defaultdict(set)
    for a, b in combinations(enumerate(R), 2):
        ia, ra = a
        ib, rb = b
        if ranges_intersect(ra, rb):
            G[ia].add(ib)
            G[ib].add(ia)
    return G

def recursive_clique_search(R: Set[int], P: Set[int], X: Set[int], G: Dict[int, Set[int]]):
    """
    https://en.wikipedia.org/wiki/Bron-Kerbosch_algorithm#With_pivoting

    R: current clique
    P: candidates
    X: excluded
    G: neighbor map
    """
    if len(P) == 0 and len(X) == 0:
        return [R]
    
    pivot = max(P.union(X), key=lambda i: len(G[i]))
    cliques = []
    for v in P.difference(G[pivot]):
        N = G[v]
        cliques.extend(recursive_clique_search(R | {v}, P & N, X & N, G))
        P.remove(v)
        X.add(v)
    return cliques

def find_cliques(G):
    return recursive_clique_search(set(), {i for i in G}, set(), G)

def find_maximum_clique(G):
    maximal_cliques = find_cliques(G)
    return max(maximal_cliques, key=lambda c: len(c))

class EvqnaSubmission(SubmissionPy):
    def origin_to_signal_boundary_distances(self, R):
        return [max(d(r, Robot(0, 0, 0, 0)) - r.radius, 0) for r in R]

    def run(self, s):
        robots = parse_robots(s)

        G = build_overlap_graph(robots)
        clique_bots = [robots[i] for i in find_maximum_clique(G)]

        return max(self.origin_to_signal_boundary_distances(clique_bots))
