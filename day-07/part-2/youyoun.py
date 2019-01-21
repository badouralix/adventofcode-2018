from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def is_required(self, elt, requirements):
        for e in requirements:
            if elt == e[1]:
                return False
        return True

    def find_required(self, requirements):
        required = set({})
        for e in requirements:
            if self.is_required(e[0], requirements):
                required.add(e[0])
        return required

    def remove_requirements(self, to_remove, requirements):
        return {e for e in requirements if e[0] != to_remove}

    def run(self, s):
        requirements = set({})
        all_chars = set({})
        for e in s.splitlines():
            b = e.split(" ")
            requirements.add((b[1], b[7]))
            all_chars.add(b[7])
            all_chars.add(b[1])
        required = sorted(self.find_required(requirements))
        for a in {e[1] for e in requirements} - {e[0] for e in requirements}:
            requirements.add((a, -1))

        if len(all_chars) < 10:
            n_workers = 2
            base_time = - 64
        else:
            n_workers = 5
            base_time = - 4

        workers = {}
        added = set({})
        t = 0
        while len(all_chars - added) > 0:
            while len(workers) < n_workers and required:
                r = required.pop(0)
                workers[r] = ord(r) + base_time
            if len(all_chars) < 10:
                print(workers)
            if len(workers) == 0:
                continue
            min_time = min({workers[e] for e in workers if workers[e] > 0})
            t += min_time
            remove = set({})
            for e in workers:
                if workers[e] > 0:
                    workers[e] -= min_time
                if workers[e] == 0:
                    remove.add(e)
                    added.add(e)
                    requirements = self.remove_requirements(e, requirements)
            for e in remove:
                workers.pop(e)
            required += [x for x in sorted(self.find_required(requirements)) if x not in required and x not in workers]
        return t
