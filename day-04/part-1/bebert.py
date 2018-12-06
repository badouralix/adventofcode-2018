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
                asleep[current_guard] = asleep.get(current_guard, 0) + int(
                    line.split(':')[1].split(']')[0]) - last_asleep

        # print(asleep)
        max_asleep = max(asleep.items(), key=lambda x: x[1])[0]
        # print(max_asleep)

        minutes = {i: 0 for i in range(60)}
        for line in times:
            if line.endswith('t'):
                current_guard = int(line.split('#')[1].split(' ')[0])
            if current_guard != max_asleep:
                continue
            if line.endswith('ep'):
                last_asleep = int(line.split(':')[1].split(']')[0])
            elif line.endswith('up'):
                for m in range(last_asleep, int(line.split(':')[1].split(']')[0])):
                    minutes[m] += 1

        # print(minutes)
        max_minutes = max(minutes.items(), key=lambda x: x[1])[0]
        # print(max_minutes)

        return max_asleep * max_minutes
