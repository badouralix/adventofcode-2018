from tool.runners.python import SubmissionPy


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

        maxi = 0
        max_id = None
        for g in guards:
            if max_id is None or guards[g] > maxi:
                max_id = g
                maxi = guards[g]

        max_time = 0
        minu = None
        for t in guard_minutes[max_id]:
            if minu is None or guard_minutes[max_id][t] > max_time:
                max_time = guard_minutes[max_id][t]
                minu = t
        return minu * max_id
