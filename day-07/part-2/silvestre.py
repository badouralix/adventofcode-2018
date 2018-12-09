from tool.runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def parse(self, s):
        # Step H must be finished before step Z can begin.
        nodes = set()
        vertices = list()
        for line in s.splitlines():
            node1, node2 = line[5], line[-12]
            nodes.add(node1)
            nodes.add(node2)
            vertices.append((node1, node2))
        return nodes, vertices

    def get_duration(self, char):
        return ord(char) - 4

    def run(self, s):
        nodes, vertices = self.parse(s)

        available = nodes - set(node for _, node in vertices)
        completed = set()
        in_progress = dict()
        time = 0

        while nodes:
            # Get work done
            finished = [char for char, done_time in in_progress.items() if done_time <= time]
            for char in finished:
                in_progress.pop(char)
                nodes.remove(char)
                completed.add(char)
                next_nodes = (b for a, b in vertices if a == char)
                for next_n in next_nodes:
                    if not set(a for a, b in vertices if b == next_n) - completed:
                        available.add(next_n)

            # Give work
            while available and len(in_progress) < 5:
                char = min(available)
                available.remove(char)
                in_progress[char] = time + self.get_duration(char)

            time += 1

        return time-1
