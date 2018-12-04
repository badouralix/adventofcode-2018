from runners.python import SubmissionPy
import numpy as np
from collections import defaultdict
from functools import partial
import re
import operator
import datetime


class ThomsSubmission(SubmissionPy):
    def run(self, s):
        guards = []
        guard_to_index = {}
        guard_id = -1
        asleep_since = None
        lines = s.split("\n")
        lines.sort()
        for line in lines:
            minute = int(line[15:17])
            m = re.match(r".* #(\d+) .*", line)
            if m:
                guard_id = int(m.group(1))
            if "falls asleep" in line:
                asleep_since = minute
            elif "wakes up" in line:
                if guard_id in guard_to_index:
                    guards[guard_to_index[guard_id]][asleep_since:minute] += 1
                else:
                    guards.append(np.zeros(60))
                    guard_to_index[guard_id] = len(guards) - 1
                    guards[-1][asleep_since:minute] += 1
                asleep_since = None

        array = np.stack(guards)
        maxi_guard_index, maxi_minute = np.unravel_index(
            np.argmax(array, axis=None), array.shape
        )
        maxi_guard = [
            key for key, value in guard_to_index.items() if value == maxi_guard_index
        ][0]
        return maxi_guard * maxi_minute
