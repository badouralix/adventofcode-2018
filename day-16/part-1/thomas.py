from tool.runners.python import SubmissionPy


class VM:
    def __init__(self):
        self.registers = [0] * 4
        self.ops = {
            "addr": self.addr,
            "addi": self.addi,
            "mulr": self.mulr,
            "muli": self.muli,
            "banr": self.banr,
            "bani": self.bani,
            "borr": self.borr,
            "bori": self.bori,
            "setr": self.setr,
            "seti": self.seti,
            "gtir": self.gtir,
            "gtri": self.gtri,
            "gtrr": self.gtrr,
            "eqir": self.eqir,
            "eqri": self.eqri,
            "eqrr": self.eqrr,
        }

    def set_registers(self, values):
        for i in range(len(values)):
            self.registers[i] = values[i]

    def addr(self, a, b, c):
        self.registers[c] = self.registers[a] + self.registers[b]

    def addi(self, a, b, c):
        self.registers[c] = self.registers[a] + b

    def mulr(self, a, b, c):
        self.registers[c] = self.registers[a] * self.registers[b]

    def muli(self, a, b, c):
        self.registers[c] = self.registers[a] * b

    def banr(self, a, b, c):
        self.registers[c] = self.registers[a] & self.registers[b]

    def bani(self, a, b, c):
        self.registers[c] = self.registers[a] & b

    def borr(self, a, b, c):
        self.registers[c] = self.registers[a] | self.registers[b]

    def bori(self, a, b, c):
        self.registers[c] = self.registers[a] | b

    def setr(self, a, b, c):
        self.registers[c] = self.registers[a]

    def seti(self, a, b, c):
        self.registers[c] = a

    def gtir(self, a, b, c):
        self.registers[c] = int(a > self.registers[b])

    def gtri(self, a, b, c):
        self.registers[c] = int(self.registers[a] > b)

    def gtrr(self, a, b, c):
        self.registers[c] = int(self.registers[a] > self.registers[b])

    def eqir(self, a, b, c):
        self.registers[c] = int(a == self.registers[b])

    def eqri(self, a, b, c):
        self.registers[c] = int(self.registers[a] == b)

    def eqrr(self, a, b, c):
        self.registers[c] = int(self.registers[a] == self.registers[b])

    @staticmethod
    def parse(s):
        return [int(c) for c in s.split()]

    def __repr__(self):
        return " ".join(self.registers)

    def possible_ops(self, before, instruction, after):
        res = set()
        for name, op in self.ops.items():
            self.set_registers(before)
            op(*instruction[1:])
            if self.registers == after:
                res.add(name)
        return res


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        vm = VM()
        part1, _ = s.split("\n\n\n")
        blocks = part1.split("\n\n")
        res = 0

        for block in blocks:
            before, instruction, after = block.splitlines()
            before = [int(n) for n in before[9:-1].split(", ")]
            after = [int(n) for n in after[9:-1].split(", ")]
            instruction = VM.parse(instruction)

            possible_ops = vm.possible_ops(before, instruction, after)

            if len(possible_ops) >= 3:
                res += 1

        return res
