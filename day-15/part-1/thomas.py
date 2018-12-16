from tool.runners.python import SubmissionPy
import numpy as np
from collections import deque

ELF = "elf"
GOBELIN = "gobelin"


def adjacent_cases(x, y):
    return [(x - 1, y), (x, y - 1), (x, y + 1), (x + 1, y)]  # reading order


class Unit:
    NEXT_ID = 10

    def __init__(self, x, y, unit_type, hp=200, ap=3):
        self.id = Unit.NEXT_ID
        self.x = x
        self.y = y
        self.type = unit_type
        self.hp = 200
        self.ap = 3

        Unit.NEXT_ID += 1

    def __repr__(self):
        return "Unit {id} ({type}): ({x},{y}) {hp} HP".format(
            id=self.id, type=self.type, hp=self.hp, x=self.x, y=self.y
        )

    def __str__(self):
        return "Unit {id} ({type}): HP{hp} ({x},{y})".format(
            id=self.id, type=self.type, hp=self.hp, x=self.x, y=self.y
        )


class Game:
    def __init__(self, world, elves, gobelins, units):
        self.world = world
        self.elves = elves
        self.gobelins = gobelins
        self.units = units
        self.nb_rounds = 0

    def find_next_move(self, unit):
        prev_pos = (unit.x, unit.y)
        frontier = deque([(adj, prev_pos) for adj in adjacent_cases(*prev_pos)])
        visited = {prev_pos: None}
        while len(frontier):
            pos, prev_pos = frontier.popleft()
            if pos not in visited:
                value = self.world[pos[0]][pos[1]]
                visited[pos] = prev_pos
                if value == 1:
                    continue
                elif value >= 10:
                    target = self.units[value]
                    if target.type == unit.type:
                        continue
                    else:
                        prev_pos = pos
                        while visited[prev_pos] != (unit.x, unit.y):
                            prev_pos = visited[prev_pos]
                        return prev_pos
                else:
                    prev_pos = pos
                    frontier.extend(
                        [(p, pos) for p in adjacent_cases(*pos) if p not in visited]
                    )
        return None

    def hit_around(self, unit):
        mini = float("inf")
        target = None
        for pos in adjacent_cases(unit.x, unit.y):
            if self.world[pos[0]][pos[1]] >= 10:
                potential_target = self.units[self.world[pos[0]][pos[1]]]
                if potential_target.type != unit.type and potential_target.hp < mini:
                    mini = potential_target.hp
                    target = potential_target

        if target is not None:
            target.hp -= unit.ap
            if target.hp <= 0:
                del self.units[target.id]
                if target.type == ELF:
                    del self.elves[target.id]
                else:
                    del self.gobelins[target.id]
                self.world[target.x][target.y] = 0
                return target.id
        return

    def play_round(self):
        killeds = []
        nb_units = len(self.units.values())
        for i, unit in enumerate(sorted(self.units.values(), key=lambda u: (u.x, u.y))):
            if unit.id in killeds:
                continue
            next_pos = self.find_next_move(unit)
            if next_pos is not None:
                if not self.world[next_pos[0]][next_pos[1]] >= 10:
                    self.world[unit.x][unit.y] = 0
                    unit.x, unit.y = next_pos
                    self.world[unit.x][unit.y] = unit.id
                killed = self.hit_around(unit)
                if killed is not None:
                    killeds.append(killed)
                if (
                    len(self.elves.values()) == 0 or len(self.gobelins.values()) == 0
                ) and not i == nb_units - 1:
                    return
        self.nb_rounds += 1

    @classmethod
    def parse(cls, s):
        world = []
        elves = {}
        gobelins = {}
        units = {}
        for x, line in enumerate(s.splitlines()):
            world_line = []
            for y, c in enumerate(line):
                if c == "#":
                    world_line.append(1)
                elif c == ".":
                    world_line.append(0)
                elif c == "G":
                    gobelin = Unit(x, y, GOBELIN)
                    world_line.append(gobelin.id)
                    gobelins[gobelin.id] = gobelin
                    units[gobelin.id] = gobelin
                elif c == "E":
                    elf = Unit(x, y, ELF)
                    world_line.append(elf.id)
                    elves[elf.id] = elf
                    units[elf.id] = elf
            world.append(world_line)
        return cls(world, elves, gobelins, units)

    def __str__(self):
        res = []
        for line in self.world:
            str_line = []
            for c in line:
                if c == 1:
                    str_line.append("#")
                elif c == 0:
                    str_line.append(".")
                else:
                    unit = self.units[c]
                    str_line.append("E" if unit.type == ELF else "G")
            res.append(" ".join(str_line))
        return "\n".join(res)

    def output(self):
        return self.nb_rounds * sum(unit.hp for unit in self.units.values())

    def run(self):
        while len(self.elves) and len(self.gobelins):
            # print("---------------")
            # print(self)
            # print(sorted(self.units.values(), key=lambda u: (u.x, u.y)))
            self.play_round()
        # print(self)
        # print(self.nb_rounds)
        # print(self.units)
        return self.output()


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        game = Game.parse(s)
        return game.run()

