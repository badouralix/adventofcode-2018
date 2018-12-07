from runners.python import SubmissionPy
from collections import defaultdict
import string


class JulesSubmission(SubmissionPy):

    def run(self, s):
        def find_next_task():
            possible = []
            for key in tasks.keys():
                if len(tasks[key]) == 0:
                    possible.append(key)
            # print(possible, tasks)
            return min(possible)


        tasks = {x: [] for x in string.ascii_uppercase}
        for line in s.split('\n'):
            elements = line.split(' ')
            tasks[elements[7]].append(elements[1])
        path = ""
        while len(tasks.keys()) != 0:
            # print("tasks {} {}".format(tasks, path))
            next_element = find_next_task()
            path += next_element
            for key in list(tasks.keys()):
                if len(tasks[key]) == 0 and key in path:
                    tasks.pop(key, None)
                    continue
                if next_element in tasks[key]:
                    tasks[key].remove(next_element)
                
        return path
