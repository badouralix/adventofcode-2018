from tool.runners.python import SubmissionPy
import re
import numpy as np


class ThomasSubmission(SubmissionPy):
    HEIGHT = 10

    def run(self, s):
        lines = s.splitlines()
        pattern = re.compile(r"< *(-?\d+), +(-?\d+)>.*< *(-?\d+), +(-?\d+)>")
        points = []
        speeds = []
        for line in lines:
            match = pattern.search(line)
            points.append([int(match.group(1)), int(match.group(2))])
            speeds.append([int(match.group(3)), int(match.group(4))])

        points = np.array(points)
        speeds = np.array(speeds)

        while True:
            points += speeds
            if np.amax(points[:, 1]) - np.amin(points[:, 1]) <= self.HEIGHT:
                xmin = np.amin(points[:, 0])
                ymin = np.amin(points[:, 1])
                points[:, 0] -= xmin
                points[:, 1] -= ymin

                data = np.zeros(np.amax(points, axis=0) + 1)
                for x, y in points:
                    data[x, y] = 1

                data = data.T

                res = []

                for i in range(data.shape[0]):
                    line = []
                    for j in range(data.shape[1]):
                        if data[i, j]:
                            line.append("#")
                        else:
                            line.append(".")
                    res.append("".join(line))
                return "\n".join(res)

            # data = np.zeros(np.amax(points, axis=0) + 1)
            # for x, y in points:
            #     data[x, y] = 1

            # data = data.T

            # if max(data.shape) < 300:
            #     for i in range(data.shape[0]):
            #         for j in range(data.shape[1]):
            #             if data[i, j]:
            #                 print("#", end="")
            #             else:
            #                 print(".", end="")
            #         print()
            #     input("Press Enter to continue...")

