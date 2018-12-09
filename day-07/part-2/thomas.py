from tool.runners.python import SubmissionPy
from collections import defaultdict
import heapq


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        lines = s.split("\n")
        requirements = defaultdict(set)
        for line in lines:
            splitted = line.split()
            from_node, to_node = splitted[1], splitted[-3]
            requirements[to_node].add(from_node)
            if not from_node in requirements:
                requirements[from_node] = set()

        ready = [task for task, value in requirements.items() if len(value) == 0]
        heapq.heapify(ready)
        requirements = {t: s for t, s in requirements.items() if len(s) != 0}
        events = []
        available_workers = 5
        t = 0
        while len(ready) > 0 or len(events) > 0:
            if len(ready) > 0 and available_workers:
                picked_task = heapq.heappop(ready)
                heapq.heappush(events, (t + 60 + ord(picked_task) - 64, picked_task))
                available_workers -= 1
                continue

            t, completed_task = heapq.heappop(events)
            available_workers += 1
            for waiting_task in list(requirements.keys()):
                if completed_task in requirements[waiting_task]:
                    if len(requirements[waiting_task]) == 1:
                        heapq.heappush(ready, waiting_task)
                        del requirements[waiting_task]
                    else:
                        requirements[waiting_task].remove(completed_task)

        return t
