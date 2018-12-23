from tool.runners.python import SubmissionPy
from collections import defaultdict, namedtuple
import heapq

# import matplotlib.pyplot as plt
# import numpy as np

NONE = 0
TORCH = 1
GEAR = 2
ITEMS = [NONE, TORCH, GEAR]

ROCKY = 0
WET = 1
NARROW = 2

POSSIBLE_ITEMS = {ROCKY: {TORCH, GEAR}, WET: {NONE, GEAR}, NARROW: {TORCH, NONE}}


class Cave:
    def __init__(self, start, target, depth):
        self.start = start
        self.target = target
        self.depth = depth
        self.erosion = {
            (start[0], start[1]): depth % 20183,
            (target[0], target[1]): depth % 20183,
        }

    def get_erosion(self, x, y):
        if (x, y) in self.erosion:
            return self.erosion[(x, y)]
        elif x == 0:
            self.erosion[(x, y)] = (y * 16807 + self.depth) % 20183
        elif y == 0:
            self.erosion[(x, y)] = (x * 48271 + self.depth) % 20183
        else:
            self.erosion[(x, y)] = (
                self.get_erosion(x - 1, y) * self.get_erosion(x, y - 1) + self.depth
            ) % 20183
        return self.erosion[(x, y)]

    def get_state(self, x, y):
        return self.get_erosion(x, y) % 3

    def get_neighbours(self, current):
        i = current[0]
        j = current[1]
        res = []
        adjacents = [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]
        for x, y in adjacents:
            if x < 0 or y < 0:
                continue
            if (
                current[2] in POSSIBLE_ITEMS[self.get_state(x, y)]
                and current[2] in POSSIBLE_ITEMS[self.get_state(i, j)]
            ):
                res.append(((x, y, current[2]), 1))
        for item in POSSIBLE_ITEMS[self.get_state(i, j)]:
            if item != current[2]:
                res.append(((i, j, item), 7))
        return res


def heuristic_cost_estimate(start, goal):
    # Manhattan distance
    return abs(goal[0] - start[0]) + abs(goal[1] - start[1])


def a_star(cave, start, goal):
    visited = set()
    distances_from_start = defaultdict(lambda: float("inf"))
    distances_from_start[start] = 0
    in_frontier = set([start])
    frontier = [(heuristic_cost_estimate(start, goal), start)]
    heapq.heapify(frontier)
    # previous = {start: None}
    # it = 0
    while len(frontier):
        # it += 1
        # if it % 10000 == 0:
        #     print_distances(distances_from_start, it)

        _, current = heapq.heappop(frontier)
        in_frontier.remove(current)

        if current == goal:
            # res = [goal]
            # while res[-1] != start:
            #     res.append(previous[res[-1]])
            # print(res[::-1])
            # print_distances(distances_from_start, "final", goal)
            return distances_from_start[goal]

        visited.add(current)

        for neighbour, dist in cave.get_neighbours(current):
            if neighbour in visited:
                continue

            distance_from_start = distances_from_start[current] + dist
            if neighbour not in in_frontier:
                in_frontier.add(neighbour)
                heapq.heappush(
                    frontier,
                    (
                        distance_from_start + heuristic_cost_estimate(neighbour, goal),
                        neighbour,
                    ),
                )
            elif distance_from_start >= distances_from_start[neighbour]:
                continue

            distances_from_start[neighbour] = distance_from_start
            # previous[neighbour] = current


def print_distances(distances_from_start, name, target=None):
    xmax = max([p[0] for p in distances_from_start.keys()])
    ymax = max([p[1] for p in distances_from_start.keys()])
    im = np.zeros((xmax + 1, ymax + 1))
    for x in range(xmax + 1):
        for y in range(ymax + 1):
            im[x, y] = min([distances_from_start[(x, y, i)] for i in ITEMS])
            if im[x, y] == float("inf"):
                im[x, y] = -1
    if target is not None:
        im[target[0], target[1]] = np.amax(im) * 2
    plt.imsave("path-{}.png".format(name), im)


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        lines = s.splitlines()

        depth = int(lines[0].split()[1])
        target_x, target_y = tuple([int(n) for n in lines[1].split()[1].split(",")])
        target = (target_x, target_y, TORCH)
        start = (0, 0, TORCH)

        cave = Cave(start, target, depth)
        return a_star(cave, start, target)

