import sys
import re
from collections import defaultdict
from functools import partial
import numpy as np


class Submission():

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        lines = s.splitlines()
        lines.sort()

        guards = defaultdict(partial(np.zeros, 60, dtype=np.uint))
        guard_id = -1
        asleep_time = None
        for row in lines:
            minutes = int(row[15:17])
            if 'Guard' in row:
                guard_id = int(re.search(r"#(\d+)", row).group(1))
            elif 'asleep' in row:
                asleep_time = minutes
            elif 'wakes up' in row:
                guards[guard_id][asleep_time:minutes] += 1
                asleep_time = None

        chosen_guard = max(guards, key=lambda x: np.sum(guards[x]))
        chosen_minute = np.argmax(guards[chosen_guard])
        return chosen_guard * chosen_minute

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
