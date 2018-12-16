from tool.runners.python import SubmissionPy

from itertools import cycle
from collections import defaultdict

class LinkedListNode(object):
    def __init__(self, val, left=None,right=None):
        self.val = val
        self.right = left
        self.left = right

class LinkedList(object):
    def __init__(self):
        self.current_node = None
        self.size = 0

    def move(self, delta):
        if self.size == 0:
            return

        if delta > 0:
            for _ in range(delta):
                self.current_node = self.current_node.right
        else:
            for _ in range(-delta):
                self.current_node = self.current_node.left

    def insert(self, val):
        node = LinkedListNode(val)
        if self.size == 0:
            node.left = node
            node.right = node
            self.current_node = node
        else:
            node.right = self.current_node.right
            node.left = self.current_node
            self.current_node.right.left = node
            self.current_node.right = node
            self.current_node = node
        self.size += 1

    def remove(self):
        left, right = self.current_node.left, self.current_node.right
        left.right = right
        right.left = left
        self.current_node = right
        self.size -= 1

    def current_val(self):
        return self.current_node.val

    def __str__(self):
        return "left %d current %d right %d" % (self.current_node.left.val, self.current_node.val, self.current_node.right.val)



class DavidSubmission(SubmissionPy):

    def play(self, players, marbles):
        circle = LinkedList()
        scores = defaultdict(int)
        pos = 0

        next_player = cycle(range(players)).__next__

        for marble in range(marbles):
            player = next_player()

            if marble % 23 == 0 and marble != 0:
                scores[player] += marble
                circle.move(-7)
                scores[player] += circle.current_val()
                circle.remove()
            else:
                circle.move(1)
                circle.insert(marble)

        return max(scores.values())

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        words = s.split(" ")
        players, marbles = (int(words[0]), int(words[6]))

        return self.play(players, marbles*100)





