from tool.runners.python import SubmissionPy

from collections import defaultdict
from string import ascii_uppercase
import bisect

class DavidSubmission(SubmissionPy):

    NUM_WORKERS = 5
    FIXED_WORK_DURATION = 60

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        count_workers = 5
        workers_state = [0]*self.NUM_WORKERS
        def wait_for_worker(after=0): # returns (w_id, t) -> w_id is the id of the worker and t is when the worker will be available
            return min(((w_id,max(t,after)) for w_id,t in enumerate(workers_state)), key=lambda x: x[1])

        def task_duration(x):
            return self.FIXED_WORK_DURATION + ord(x) - 64

        relationships = []
        for line in s.split("\n"):
            x = line.split(" ")
            relationships.append((x[1], x[7]))

        dependencies = defaultdict(set)
        reversed_dependencies = defaultdict(set)

        for a,b in relationships:
            dependencies[b].add(a)
            reversed_dependencies[a].add(b)

        activated = dict()
        roots = (set(reversed_dependencies.keys()) - set(dependencies.keys()))
        to_visit = {x:0 for x in roots}

        while len(to_visit)>0:
            # t0 is the time at which the step can be started
            w_id, t0, step = min(((*wait_for_worker(t), step) for step,t in to_visit.items()), key=lambda x: (x[1],x[2]))
            t1 = t0 + task_duration(step)
            # print(w_id, step, t0, t1, workers_state, to_visit)
            activated[step] = t1
            workers_state[w_id] = t1
            del to_visit[step]
            for c in reversed_dependencies[step]:
                if all(dep in activated for dep in dependencies[c]):
                    to_visit[c] = (max(activated[dep] for dep in dependencies[c]))
        return max(workers_state)
