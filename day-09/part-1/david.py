from runners.python import SubmissionPy

from itertools import cycle
from collections import defaultdict

class DavidSubmission(SubmissionPy):

    def play(self, players, marbles):
        circle = []
        scores = defaultdict(int)
        pos = 0

        next_player = cycle(range(players)).__next__

        for marble in range(marbles):
            player = next_player()

            if marble % 23 == 0 and marble != 0:
                scores[player] += marble
                next_pos = (pos - 7) % len(circle)
                scores[player] += circle[next_pos]
                del circle[next_pos]
                pos = next_pos
            else:
                next_pos = 0
                if len(circle) == 0:
                    next_pos = 1
                else:
                    next_pos = ((pos+1) % len(circle)) + 1
                circle.insert(next_pos, marble)
                pos = next_pos

        return max(scores.values())

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        words = s.split(" ")
        players, marbles = (int(words[0]), int(words[6]))

        return self.play(players, marbles)


