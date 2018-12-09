from runners.python import SubmissionPy


class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        players = int(s.split(' ')[0])
        last = int(s.split(' ')[-2])
        marbles = [0]
        player_scores = [0] * players
        current = 0
        for mar in range(last):
            player = mar % players
            marble = mar + 1
            if marble % 23 != 0:
                current = (current + 2) % len(marbles)
                marbles.insert(current, marble)
                continue
            player_scores[player] += marble
            to_remove = (current - 7 + len(marbles)) % len(marbles)
            score = marbles[to_remove]
            player_scores[player] += score
            marbles.remove(score)
            current = to_remove
        return max(player_scores)
