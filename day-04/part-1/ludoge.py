from tool.runners.python import SubmissionPy


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

        sleep_duration = {k: len(v) for k, v in guards.items()}
        max_guard = max(sleep_duration, key=sleep_duration.get)
        max_guard_sleeps = guards[max_guard]
        max_minute = max(set(max_guard_sleeps), key=max_guard_sleeps.count)

        return max_guard * max_minute
        pass
