from tool.runners.python import SubmissionPy
import numpy as np


def string_to_list(s):
    return [int(c == "#") for c in s]


def list_to_string(l):
    return "".join(["#" if x else "." for x in l])


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        lines = s.splitlines()
        garden1 = lines[0].split()[2]
        garden1 = string_to_list(garden1)
        garden2 = list(garden1)
        previous, current = garden1, garden2
        patterns = {}
        offset = 0
        for i in range(2, len(lines)):
            before, after = lines[i].split(" => ")
            patterns[before] = int(after == "#")

        for gen in range(20):
            # print(gen, list_to_string(current), offset)
            previous = [0] * 5 + previous + [0] * 5
            current = [0] * 5 + current + [0] * 5
            offset += 5

            for i in range(2, len(previous) - 3):
                pattern = list_to_string(previous[i - 2 : i + 3])
                current[i] = patterns[pattern] if pattern in patterns else 0

            current = np.trim_zeros(current, "f")
            offset -= len(previous) - len(current)
            current = np.trim_zeros(current, "b")
            previous = list(current)

        # print(gen + 1, list_to_string(current), offset)
        res = 0
        for i in range(len(current)):
            if current[i]:
                res += i - offset

        return res
