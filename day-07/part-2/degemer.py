from runners.python import SubmissionPy

def select_next(deps, done):
    for let in deps:
        if len(deps[let]) == 0 and let not in done:
            return let
    return None

class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        deps = {}
        order = ''
        for line in s.splitlines():
            parsed = line.split(' ')
            before, after = parsed[1], parsed[-3]
            if after not in deps:
                deps[after] = set()
            if before not in deps:
                deps[before] = set()
            deps[after].add(before)

        workers = 5
        add = 60
        workers_next = [None] * workers
        workers_task = [None] * workers
        ss = 'abcdefghijklmnopqrstuvwxyz'.upper()
        time = 0
        done = set()
        while len(deps) > 0:
            if not any(a is None or a == time for a in workers_next):
                time += 1
                continue
            while any(a == time for a in workers_next):
                i = workers_next.index(time)
                if workers_task[i] is not None:
                    select = workers_task[i]
                    del deps[select]
                    for let in deps:
                        if select in deps[let]:
                            deps[let].remove(select)

                select = select_next(deps, done)
                if select is None:
                    workers_next[i] = None
                    workers_task[i] = None
                else:
                    done.add(select)
                    workers_task[i] = select
                    workers_next[i] = time + add + (ss.find(select) + 1)
            select = select_next(deps, done)
            while select is not None and any(a is None for a in workers_next):
                done.add(select)
                i = workers_next.index(None)
                workers_task[i] = select
                workers_next[i] = time + add + (ss.find(select) + 1)
                select = select_next(deps, done)
            time += 1

        return time-1
