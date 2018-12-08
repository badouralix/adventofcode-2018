from runners.python import SubmissionPy
from collections import defaultdict
import string
import time


class JulesSubmission(SubmissionPy):

    def run(self, s):
        def find_next_task():
            possible = []
            for key in tasks.keys():
                if len(tasks[key]) == 0:
                    possible.append(key)
            for worker in workers:
                if worker[0] in possible:
                    possible.remove(worker[0]) # We're working on it
            if len(possible) == 0:
                return None
            return min(possible)


        tasks = {x: [] for x in string.ascii_uppercase}
        for line in s.split('\n'):
            elements = line.split(' ')
            tasks[elements[7]].append(elements[1])

        path = ""
        current_time = -1 # Since we start by incrementing
        workers = [["", 0] for _ in range(5)]
        index = 0
        while len(tasks.keys()) != 0:
            current_time += 1
            # Everybody's working my friend
            if all([(worker[1] > current_time) for worker in workers]):
                continue
            # Remove done workers
            for worker in workers:
                if worker[0] != "" and worker[1] <= current_time:
                    key = worker[0]
                    worker[0] = ""
                    # Remove tasks where it's needed
                    for task_key in tasks.keys():
                        if key in tasks[task_key]:
                            tasks[task_key].remove(key)
                    # Pop the key
                    if len(tasks[key]) == 0 and key in path:
                        tasks.pop(key, None)
                        continue
            for worker in workers:
                if worker[1] <= current_time:
                    next_element = find_next_task()
                    if next_element is None or next_element in path:
                        continue
                    path += next_element
                    worker[0] = next_element
                    worker[1] = current_time + 60 + 1 + string.ascii_uppercase.index(next_element)
        return current_time

        
