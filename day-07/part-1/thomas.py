from runners.python import SubmissionPy
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
        ordered_tasks = []
        while len(ready) > 0:
            task = heapq.heappop(ready)
            ordered_tasks.append(task)
            for waiting_task in list(requirements.keys()):
                if task in requirements[waiting_task]:
                    if len(requirements[waiting_task]) == 1:
                        heapq.heappush(ready, waiting_task)
                        del requirements[waiting_task]
                    else:
                        requirements[waiting_task].remove(task)
        return "".join(ordered_tasks)
