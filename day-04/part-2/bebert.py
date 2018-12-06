from runners.python import SubmissionPy


class BebertSubmission(SubmissionPy):

    def run(self, s):
        times = sorted(s.splitlines())
        asleep = {}
        current_guard = 0
        last_asleep = 0
        for line in times:
            if line.endswith('t'):
                current_guard = int(line.split('#')[1].split(' ')[0])
            elif line.endswith('ep'):
                last_asleep = int(line.split(':')[1].split(']')[0])
            elif line.endswith('up'):
                if current_guard not in asleep:
                    asleep[current_guard] = {i: 0 for i in range(60)}
                for m in range(last_asleep, int(line.split(':')[1].split(']')[0])):
                    asleep[current_guard][m] += 1

        max_guard = 0
        max_minute = 0
        max_minute_value = 0
        for guard, guard_asleep in asleep.items():
            for m, minutes_asleep in guard_asleep.items():
                if minutes_asleep > max_minute_value:
                    max_minute_value = minutes_asleep
                    max_guard = guard
                    max_minute = m

        print(max_guard)
        print(max_minute)
        return max_guard * max_minute
