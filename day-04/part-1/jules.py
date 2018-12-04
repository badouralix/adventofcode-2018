from runners.python import SubmissionPy
from collections import defaultdict
import operator

class JulesSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        instructions = {}
        for line in s.split("\n"):
            elements = line.split(' ')
            instructions[" ".join(elements[:2])] = " ".join(elements[2:])
        cur_id = 0
        guards = defaultdict(int)
        guards_max = defaultdict(int)
        max_sleep = defaultdict(lambda: defaultdict(int))
        for time in sorted(instructions.keys()):
            elements = instructions[time].split(' ')
            if elements[1].startswith('#'):
                cur_id = int(elements[1][1:])
                wake_up = int(time.split(':')[-1][:-1])
            if "wakes up" in instructions[time]:
                wake_up = int(time.split(':')[-1][:-1])
                duration = int(time.split(':')[-1][:-1]) - sleep
                guards[cur_id] += duration
                for i in range(sleep, wake_up):
                    max_sleep[cur_id][i] += 1
            if "falls asleep" in instructions[time]:
                sleep = int(time.split(':')[-1][:-1])
        chosen_id = max(guards.items(), key=operator.itemgetter(1))[0]
        return chosen_id*(max(max_sleep[chosen_id].items(), key=operator.itemgetter(1))[0])
