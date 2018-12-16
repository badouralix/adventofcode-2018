from tool.runners.python import SubmissionPy
from collections import defaultdict
import operator

class JulesSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        cur_id = 0
        guards = defaultdict(int)
        max_sleep = defaultdict(lambda: defaultdict(int))
        for line in sorted(s.split('\n')):
            elements = line.split(' ')
            if elements[3].startswith('#'):
                cur_id = int(elements[3][1:])
                wake_up = int(line.split(':')[-1][:2])
            if "wakes up" in line:
                wake_up = int(line.split(':')[-1][:2])
                duration = wake_up - sleep
                guards[cur_id] += duration
                for i in range(sleep, wake_up):
                    max_sleep[cur_id][i] += 1
            if "falls asleep" in line:
                sleep = int(line.split(':')[-1][:2])
        total_max = 0
        for cur_id, el in max_sleep.items():
            new_max = max(el.items(), key=operator.itemgetter(1))[1]
            if new_max > total_max:
                chosen_id = cur_id
                total_max = new_max
        return chosen_id*max(max_sleep[chosen_id].items(), key=operator.itemgetter(1))[0]
