from tool.runners.python import SubmissionPy
from collections import namedtuple


class Cart:
    def __init__(self, x, y, direction, next_turn):
        self.x = x
        self.y = y
        self.dir = direction
        self.next_turn = next_turn

    def __str__(self):
        return "({},{},{},{})".format(self.x, self.y, self.dir, self.next_turn)


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        lines = s.splitlines()
        world = []
        carts = []
        rail_chars = "|\\/+-"
        char_to_int = {" ": 0}
        char_to_int.update({char: 1 for char in rail_chars})
        char_to_int.update(
            {
                "|": 1,
                "\\": 2,
                "/": 3,
                "+": 4,
                "-": 5,
                "v": 11,
                "<": 15,
                "^": 11,
                ">": 15,
            }
        )
        cart_char_to_dir = {"v": 3, "<": 0, "^": 1, ">": 2}
        for y in range(len(lines)):
            row = []
            for x in range(len(lines[y])):
                char = lines[y][x]
                row.append(char_to_int[char])
                if char in cart_char_to_dir.keys():
                    carts.append(Cart(x, y, cart_char_to_dir[char], 0))
            world.append(row)

        to_remove = []
        while True:
            carts.sort(key=lambda cart: (cart.y, cart.x))
            for idx, cart in enumerate(carts):
                if idx in to_remove:
                    continue

                x, y = cart.x, cart.y

                if world[y][x] % 10 == 2:
                    if cart.dir == 0:
                        cart.dir = 1
                    elif cart.dir == 1:
                        cart.dir = 0
                    elif cart.dir == 2:
                        cart.dir = 3
                    elif cart.dir == 3:
                        cart.dir = 2

                if world[y][x] % 10 == 3:
                    if cart.dir == 0:
                        cart.dir = 3
                    elif cart.dir == 1:
                        cart.dir = 2
                    elif cart.dir == 2:
                        cart.dir = 1
                    elif cart.dir == 3:
                        cart.dir = 0

                if world[y][x] % 10 == 4:
                    if cart.next_turn == 0:
                        cart.dir = (cart.dir - 1) % 4
                    elif cart.next_turn == 2:
                        cart.dir = (cart.dir + 1) % 4
                    cart.next_turn = (cart.next_turn + 1) % 3

                if cart.dir == 0:
                    cart.x -= 1
                elif cart.dir == 1:
                    cart.y -= 1
                elif cart.dir == 2:
                    cart.x += 1
                elif cart.dir == 3:
                    cart.y += 1

                world[y][x] -= 10

                if world[cart.y][cart.x] >= 10:
                    to_remove.append(idx)
                    for i, c in enumerate(carts):
                        if c.x == cart.x and c.y == cart.y and i != idx:
                            world[c.y][c.x] -= 10
                            to_remove.append(i)
                            break
                else:
                    world[cart.y][cart.x] += 10

            if len(to_remove) > 0:
                carts = [c for i, c in enumerate(carts) if i not in to_remove]
                to_remove = []

            if len(carts) == 1:
                break

        return "{},{}".format(carts[0].x, carts[0].y)
