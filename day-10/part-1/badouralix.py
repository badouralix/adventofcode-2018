from tool.runners.python import SubmissionPy

import re


class BadouralixPoint():

    def __init__(self, pos_x, pos_y, vel_x, vel_y):
        self.pos_x = pos_x
        self.pos_y = pos_y
        self.vel_x = vel_x
        self.vel_y = vel_y

    def step(self):
        self.pos_x += self.vel_x
        self.pos_y += self.vel_y


class BadouralixSubmission(SubmissionPy):
    HEIGHT = 10
    WIDTH = 62

    def run(self, s):
        points = []

        for line in s.split("\n"):
            (pos_x, pos_y, vel_x, vel_y) = re.findall(r"-?\d+", line)
            points.append(BadouralixPoint(int(pos_x), int(pos_y), int(vel_x), int(vel_y)))

        while True:
            y = []

            for point in points:
                point.step()
                y.append(point.pos_y)

            if max(y) - min(y) <= self.HEIGHT:
                return self.reader(points)

    def reader(self, points):
        min_x = min(p.pos_x for p in points)
        min_y = min(p.pos_y for p in points)

        img = [[False for _ in range(self.HEIGHT)] for _ in range(self.WIDTH)]
        for p in points:
            img[p.pos_x - min_x][p.pos_y - min_y] = True

        for i in range(self.HEIGHT):
            for j in range(self.WIDTH):
                if img[j][i]:
                    print("#", end='')
                else:
                    print(".", end='')
            print()

        return ""
