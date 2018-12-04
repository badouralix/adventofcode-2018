from runners.python import SubmissionPy


class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        lines = s.splitlines()
        lines = sorted(lines)
        current_id = None
        guards = {}
        guard_minutes = {}
        start = None
        for line in lines:
            if 'shift' in line:
                current_id = int(line.split('#')[1].split(' ')[0])
            elif 'asleep' in line:
                start = int(line.split(']')[0].split(':')[-1])
            else:
                end = int(line.split(']')[0].split(':')[-1])
                guards[current_id] = guards.get(current_id, 0) + end - start
                if current_id not in guard_minutes:
                    guard_minutes[current_id] = {}
                for i in range(start, end):
                    guard_minutes[current_id][i] = guard_minutes[current_id].get(i, 0) + 1

        minu = None
        guard = None
        for g in guards:
            for t in guard_minutes[g]:
                if guard is None or guard_minutes[g][t] > guard_minutes[guard][minu]:
                    guard = g
                    minu = t
        return minu * guard
