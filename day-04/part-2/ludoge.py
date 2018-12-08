from runners.python import SubmissionPy
from collections import Counter

class LudogeSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        lines = sorted(s.splitlines())
        guards = {}
        for line in lines:
            minute = int(line.split()[1][3:5])
            if "#" in line:
                guard_id = int(line.split()[3][1:])
                if guard_id not in guards:
                    guards[guard_id] = []
                wakes_up = minute
            if "falls asleep" in line:
                falls_asleep = minute
            if "wakes up" in line:
                wakes_up = minute
                guards[guard_id] += list(range(falls_asleep, wakes_up))


        guard_minute_frequency = {k: dict(Counter(v)) for k, v in guards.items() if Counter(v)}
        guard_minute_max = {k: max(v.values()) for k, v in guard_minute_frequency.items()}
        max_guard = max(guard_minute_frequency, key=guard_minute_max.get)
        max_guard_sleeps = guards[max_guard]
        max_minute = max(set(max_guard_sleeps), key=max_guard_sleeps.count)

        return max_minute * max_guard

        pass
