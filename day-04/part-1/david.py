from runners.python import SubmissionPy

import re
from collections import defaultdict
class DavidSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        logs = sorted(s.split("\n"))
        current_id = None
        time_falls_asleep = dict()
        total_sleep_time = defaultdict(int)
        minutes_asleep = dict()
        for log in logs:
            if "begins shift" in log:
                current_id = int(re.findall(r'-?\d+', log[18:])[0])
                if current_id not in minutes_asleep:
                    minutes_asleep[current_id] = defaultdict(int)
            elif "falls asleep" in log:
                h = int(log[12:14])
                m = int(log[15:17])
                time_falls_asleep[current_id] = (h,m)
            elif "wakes up" in log:
                h1 = int(log[12:14])
                m1 = int(log[15:17])
                h0, m0 = time_falls_asleep[current_id]
                delta_min = h1*60 + m1 - (h0*60 + m0)
                print(h1,m1,h0,m0)

                total_sleep_time[current_id] += delta_min
                for i in range(delta_min):
                    minutes_asleep[current_id][m0 + i] += 1

        c_max, _ = max(total_sleep_time.items(), key=lambda x:x[1])
        m_max,_ = max(minutes_asleep[c_max].items(), key=lambda x:x[1] )
        return c_max * m_max
