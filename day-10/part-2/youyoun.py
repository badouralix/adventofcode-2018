from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def update_position(self, positions, velocities):
        for i in positions:
            positions[i] = positions[i][0] + velocities[i][0], positions[i][1] + velocities[i][1]

    def run(self, s):
        lines = s.splitlines()
        positions = {}
        velocities = {}
        for i, line in enumerate(lines):
            x, y = int(line[10:16]), int(line[18:24])
            v_x, v_y = int(line[36:38]), int(line[40:42])
            positions[i] = x, y
            velocities[i] = v_x, v_y

        seconds = 0
        while True:
            is_close = True
            for i in range(len(positions) - 1):
                if abs(positions[i][1] - positions[i + 1][1]) > 10:
                    is_close = False
                    break
            if is_close:
                break
            self.update_position(positions, velocities)
            seconds += 1

        return seconds

