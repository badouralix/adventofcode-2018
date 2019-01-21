import re
from tool.runners.python import SubmissionPy

class Node:

    def __init__(self, data, right=None, left=None):
        self.data = data
        self.right = right
        self.left = left

class LinkedList:

    def __init__(self):
        self.size = 0
        self.current_node = None

    def insert(self, new_data):
        node = Node(new_data)
        if self.size == 0:
            node.right = node
            node.left = node
            self.current_node = node  
        else:
            node.right = self.current_node.right
            node.left = self.current_node
            self.current_node.right.left = node
            self.current_node.right = node
            self.current_node = node
        self.size += 1

    def pop(self):
        self.current_node.right.left = self.current_node.left
        self.current_node.left.right = self.current_node.right
        data = self.current_node.data
        self.current_node = self.current_node.right
        self.size -= 1
        return data

    def move(self, i):
        if self.size == 0:
            return
        if i > 0:
            for _ in range(i):
                self.current_node = self.current_node.right
        else:
            for _ in range(-i):
                self.current_node = self.current_node.left

class SilvestreSubmission(SubmissionPy):

    def run(self, s):
        n_players, last_marble = tuple(map(int, re.match(r"^(\d+)[a-z; ]+(\d+)", s).groups()))
        scores = [0 for _ in range(n_players)]
        marbles = LinkedList()
        marbles.insert(0)
        for i in range(1, 100 * last_marble + 1):
            if i % 23 != 0:
                marbles.move(1)
                marbles.insert(i)
            else:
                marbles.move(-7)
                scores[i % n_players] += i + marbles.pop()
        return max(scores)