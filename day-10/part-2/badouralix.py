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

    def run(self, s):
        points = []

        for line in s.split("\n"):
            (pos_x, pos_y, vel_x, vel_y) = re.findall(r"-?\d+", line)
            points.append(BadouralixPoint(int(pos_x), int(pos_y), int(vel_x), int(vel_y)))

        seconds = 0

        while True:
            y = []

            for point in points:
                point.step()
                y.append(point.pos_y)

            seconds += 1

            if max(y) - min(y) <= self.HEIGHT:
                return seconds
