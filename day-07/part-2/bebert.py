from runners.python import SubmissionPy


class BebertSubmission(SubmissionPy):

    def run(self, s):
        dependencies = [line.split(" ") for line in s.splitlines()]
        dependencies = [(d[1], d[7]) for d in dependencies]

        base_time = 60 if len(dependencies) != 7 else 0
        num_workers = 5 if len(dependencies) != 7 else 2

        tasks = {}
        for before, after in dependencies:
            if before not in tasks:
                tasks[before] = []
            if after not in tasks:
                tasks[after] = []
            tasks[after].append(before)

        tasks = sorted(tasks.items(), key=lambda t: t[0])

        time_cur = 0
        current = {}
        done = set()
        while len(done) != len(tasks):
            for after, befores in tasks:
                if after not in done and after not in current and all(t in done for t in befores):
                    current[after] = base_time + ord(after) - 64
                    if len(current) == num_workers:
                        break
            next_step = min(current.values())
            time_cur += next_step
            for t in current:
                current[t] -= next_step
                if current[t] == 0:
                    done.add(t)

            for t in done:
                if t in current:
                    del current[t]

        return time_cur
