from runners.python import SubmissionPy


class JulesSubmission(SubmissionPy):

    def run(self, s):
        elements = s.split(' ')
        players = int(elements[0])
        points = int(elements[-2])
        marbles = [0]
        current = 0
        scores = [0]*players
        for i in range(1, points + 1):
            if i % 23 != 0:
                current += 2
                current %= len(marbles)
                marbles.insert(current, i)
            else:
                current = (current - 7) % len(marbles)
                scores[i%players] += i + marbles[current]
                marbles.remove(marbles[current])
        return max(scores)
