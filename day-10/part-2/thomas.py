from tool.runners.python import SubmissionPy
import re
import numpy as np


class ThomasSubmission(SubmissionPy):
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

        time = 0
        while True:
            time += 1
            points += speeds

            if np.amax(points) < 300:
                data = np.zeros(np.amax(points, axis=0) + 1)
                for x, y in points:
                    data[x, y] = 1

                data = data.T
                for i in range(data.shape[0]):
                    for j in range(data.shape[1]):
                        if data[i, j]:
                            print("#", end="")
                        else:
                            print(".", end="")
                    print()
                print("**********", time, "s **********\n")
                input("Press Enter to continue...")

