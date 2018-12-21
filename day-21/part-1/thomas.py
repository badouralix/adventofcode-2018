from tool.runners.python import SubmissionPy


class VM:
    def __init__(self, ip_register):
        self.registers = [0] * 6
        self.ip_register = ip_register
        self.registers[self.ip_register] = -1
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

    @property
    def ip(self):
        return self.registers[self.ip_register]

    @ip.setter
    def ip(self, n):
        self.registers[self.ip_register] = n

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

    def load(self, program):
        self.program = program

    def run(self, verbose=False):
        while True:
            self.ip += 1
            if self.ip < 0 or self.ip >= len(self.program):
                return
            else:
                op, a, b, c = self.program[self.ip].split()
                if verbose:
                    print(self.ip, op, a, b, c, "|", self)
                if self.ip == 28:
                    return self.registers[2]
                self.ops[op](int(a), int(b), int(c))

    def __repr__(self):
        return " ".join([str(n) for n in self.registers])


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        lines = s.splitlines()
        ip_register = int(lines[0].split()[1])
        vm = VM(ip_register=ip_register)
        vm.load(lines[1:])
        return vm.run()
