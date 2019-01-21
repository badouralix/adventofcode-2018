from tool.runners.python import SubmissionPy
import re


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        sorted_input = sorted(s.splitlines())
        minute_logs = []
        for log in sorted_input:
            parsed_input = re.search(r"^\[\d+-\d+-\d+\s\d+:(\d+)\]\s(.*)", log.strip())
            minutes = int(parsed_input.group(1))
            log_text = parsed_input.group(2)
            minute_logs.append((minutes, log_text))
        i = 0
        guards_sleep_durations = {}
        guards_sleep_schedule = {}
        while i < len(minute_logs):
            parsed_text = re.search(r"Guard\s#(\d+)\s.*", minute_logs[i][1])
            current_guard = parsed_text.group(1)
            j = i + 1
            start_time = 0
            while j < len(minute_logs):
                if minute_logs[j][1] == "falls asleep":
                    start_time = minute_logs[j][0]
                elif minute_logs[j][1] == "wakes up":
                    end_time = minute_logs[j][0]
                    if current_guard in guards_sleep_durations:
                        guards_sleep_durations[current_guard] += end_time - start_time
                        for k in range(start_time, end_time):
                            guards_sleep_schedule[current_guard][k] += 1
                    else:
                        guards_sleep_durations[current_guard] = end_time - start_time
                        guards_sleep_schedule[current_guard] = [0] * 60
                        for k in range(start_time, end_time):
                            guards_sleep_schedule[current_guard][k] += 1
                else:
                    break
                j += 1
            i = j

        guard_id = next(filter(lambda guard: guards_sleep_durations[guard] == max(guards_sleep_durations.values()),
                               guards_sleep_durations), None)
        longuest_minute = guards_sleep_schedule[guard_id].index(max(guards_sleep_schedule[guard_id]))
        return longuest_minute * int(guard_id)
