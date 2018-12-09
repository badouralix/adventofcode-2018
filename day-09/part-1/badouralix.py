from runners.python import SubmissionPy


class BadouralixSubmission(SubmissionPy):

    def run(self, s):
        split = s.split(" ")
        players = int(split[0])
        last = int(split[6])
        # print(players, last)

        scores = [0] * players
        marbles = [0]
        pos = 0
        player = 1

        for m in range(last + 1):
            if m % 23 != 0:
                size = len(marbles)
                pos_l = (pos + 1) % size
                pos_r = (pos + 2) % size
                if pos_r == 0:
                    marbles = marbles + [m]
                    # pos = len(marbles) - 1
                else:
                    marbles = marbles[:pos_l + 1] + [m] + marbles[pos_r:]
                pos = pos_l + 1
            else:
                scores[player] += m
                pos = (pos - 7) % len(marbles)
                scores[player] += marbles[pos]
                marbles = marbles[:pos] + marbles[(pos + 1) % len(marbles):]

            player += 1
            player %= players

            if m < 1000:
                print(scores)

        return max(scores)
