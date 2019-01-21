from tool.runners.python import SubmissionPy


class BebertSubmission(SubmissionPy):

    def run(self, s):
        dependencies = [line.split(" ") for line in s.splitlines()]
        dependencies = [(d[1], d[7]) for d in dependencies]

        tasks = {}
        for before, after in dependencies:
            if before not in tasks:
                tasks[before] = []
            if after not in tasks:
                tasks[after] = []
            tasks[after].append(before)

        tasks = sorted(tasks.items(), key=lambda t: t[0])

        done_ord = []
        done = set()
        while len(done) != len(tasks):
            for after, befores in tasks:
                if after not in done and all(t in done for t in befores):
                    done.add(after)
                    done_ord.append(after)
                    break

        return "".join(done_ord)
