from tool.runners.python import SubmissionPy
import numpy as np


class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        s = s.splitlines()
        # 0 nothing, 1 horizontal, 2 vertical, 3 /, 4 \, 5 + intersect
        store = np.zeros((len(s), len(s[0])), dtype=np.int)
        # carts = i, j, dir (0 up, 1 right, 2 down, 3 left), state 0, 1, 2
        carts = []
        for i, line in enumerate(s):
            for j, el in enumerate(line):
                if el == ' ':
                    continue
                elif el == '-':
                    store[i, j] = 1
                elif el == '|':
                    store[i, j] = 2
                elif el == '/':
                    store[i, j] = 3
                elif el == '\\':
                    store[i, j] = 4
                elif el == '+':
                    store[i, j] = 5
                elif el == '>':
                    store[i, j] = 1
                    carts.append([i, j, 1, 0])
                elif el == '<':
                    store[i, j] = 1
                    carts.append([i, j, 3, 0])
                elif el == 'v':
                    store[i, j] = 2
                    carts.append([i, j, 0, 0])
                elif el == '^':
                    store[i, j] = 2
                    carts.append([i, j, 2, 0])
                else:
                    raise Exception("WTF AA%sAA" % el)
        while True:
            new_carts = []
            for x, y, direct, state in carts:
                if store[x, y] == 5:
                    if state == 0:
                        direct = (direct + 1) % 4
                    #elif state == 1:
                    #    direct = (direct + 2) % 4
                    elif state == 2:
                        direct = (direct - 1 + 4) % 4

                    state = (state + 1) % 3
                # /
                # carts = i, j, dir (2 up, 1 right, 0 down, 3 left), state 0, 1, 2
                elif store[x, y] == 3:
                    if direct == 0:
                        direct = 3
                    elif direct == 1:
                        direct = 2
                    elif direct == 2:
                        direct = 1
                    elif direct == 3:
                        direct = 0
                # \
                elif store[x, y] == 4:
                    if direct == 0:
                        direct = 1
                    elif direct == 1:
                        direct = 0
                    elif direct == 2:
                        direct = 3
                    elif direct == 3:
                        direct = 2
                x, y = move(x, y, direct)
                new_carts.append([x, y, direct, state])

            carts = new_carts
            # check collision
            accidents = set()
            for i, cart in enumerate(carts):
                if i in accidents:
                    continue

                x = cart[0]
                y = cart[1]
                for j, cart1 in enumerate(carts[i + 1:]):
                    x1 = cart1[0]
                    y1 = cart1[1]

                    if x == x1 and y1 == y:
                        accidents.add(i)
                        accidents.add(i + j + 1)
                        break
            carts = [cart for i, cart in enumerate(carts) if i not in accidents]
            if len(carts) == 1:
                return '%d,%d' % (carts[0][1], carts[0][0])


def move(x, y, direct):
    if direct == 0:
        return (x + 1, y)
    elif direct == 1:
        return (x, y + 1)
    elif direct == 2:
        return (x - 1, y)
    elif direct == 3:
        return (x, y - 1)
    else:
        raise Exception("Bad direct AA%sAA" % direct)
