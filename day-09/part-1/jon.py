from runners.python import SubmissionPy


class JonSubmission(SubmissionPy):

    def run(self, s):
        words = s.split(" ")
        nbPlayers = int(words[0])
        nbMarbles = int(words[6])

        n0 = Node(0, 0 ,0)
        n0.prev = n0
        n0.next = n0

        curr = n0
        scores = dict()

        for turn in range(1, nbMarbles+1):
            #printList(curr)
            #if turn == 26:
            #    break

            if turn % 23 == 0:
                player = (turn % nbPlayers) +1
                curr = curr.prev.prev.prev.prev.prev.prev.prev
                scores[player] = scores.get(player, 0) + turn + curr.value
                curr.prev.next = curr.next
                curr = curr.next
            else:
                new = Node(turn, curr.next, curr.next.next)
                curr.next.next.prev = new
                curr.next.next = new
                curr = new

        return max(scores.values())

class Node:
    def __init__(self, value, prev, nnext):
        self.value = value
        self.prev = prev
        self.next = nnext

def printList(curr):
    l = [curr.value]
    c = curr.next
    while c != curr:
        l.append(c.value)
        c = c.next
    print(l)
