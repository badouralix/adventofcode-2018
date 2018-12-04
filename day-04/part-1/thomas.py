import sys
import numpy as np
from collections import defaultdict
from functools import partial
import re
import operator
import datetime


class Submission():
    def run(self, s):
        guards = defaultdict(partial(np.zeros, 60))
        guard_id = -1
        asleep_since = None
        lines = s.split("\n")
        lines.sort()
        for line in lines:
            minute = int(line[15:17])
            m = re.match(r".* #(\d+) .*", line)
            if m:
                guard_id = int(m.group(1))
            elif "falls asleep" in line:
                asleep_since = minute
            elif "wakes up" in line:
                guards[guard_id][asleep_since:minute] += 1
                asleep_since = None
        chosen_guard = max([(np.sum(l), guard_id) for guard_id, l in guards.items()])[1]
        chosen_minute = np.argmax(guards[chosen_guard])
        return chosen_guard * chosen_minute

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
