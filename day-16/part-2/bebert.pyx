cdef int addr(reg, a, b):
    return reg[a] + reg[b]

cdef int addi(reg, a, b):
    return reg[a] + b

cdef int mulr(reg, a, b):
    return reg[a] * reg[b]

cdef int muli(reg, a, b):
    return reg[a] * b

cdef int banr(reg, a, b):
    return reg[a] & reg[b]

cdef int bani(reg, a, b):
    return reg[a] & b

cdef int borr(reg, a, b):
    return reg[a] | reg[b]

cdef int bori(reg, a, b):
    return reg[a] | b

cdef int setr(reg, a, b):
    return reg[a]

cdef int seti(reg, a, b):
    return a

cdef int gtir(reg, a, b):
    if a > reg[b]:
        return 1
    else:
        return 0

cdef int gtri(reg, a, b):
    if reg[a] > b:
        return 1
    else:
        return 0

cdef int gtrr(reg, a, b):
    if reg[a] > reg[b]:
        return 1
    else:
        return 0

cdef int eqir(reg, a, b):
    if a == reg[b]:
        return 1
    else:
        return 0

cdef int eqri(reg, a, b):
    if reg[a] == b:
        return 1
    else:
        return 0

cdef int eqrr(reg, a, b):
    if reg[a] == reg[b]:
        return 1
    else:
        return 0


functions = [addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr]


cpdef int run(s):
    cdef int i, o, a, b, c, res
    cdef bint ok

    cdef int before[4]
    cdef int after[4]

    cdef int state = 0

    possible = {x: {y for y in range(16)} for x in range(16)}

    part1, part2 = s.split("\n\n\n")
    part1 = part1 + "\n"

    for line in part1.splitlines():
        if line.startswith("B"):
            state = 1
            x0, x1, x2, x3 = line.split("[")[1].strip("\n\r ]").split(",")
            before[0] = int(x0)
            before[1] = int(x1)
            before[2] = int(x2)
            before[3] = int(x3)

        elif line.startswith("A"):
            state = 3
            x0, x1, x2, x3 = line.split("[")[1].strip("\n\r ]").split(",")
            after[0] = int(x0)
            after[1] = int(x1)
            after[2] = int(x2)
            after[3] = int(x3)

        elif line.strip() == "":
            state = 0
            for fi, f in enumerate(functions):
                res = f(before, a, b)
                for i in range(4):
                    if i == c:
                        if res != after[i]:
                            possible[o].discard(fi)
                            break
                    else:
                        if before[i] != after[i]:
                            possible[o].discard(fi)
                            break

        else:
            state = 2
            x0, x1, x2, x3 = line.split(" ")
            o = int(x0)
            a = int(x1)
            b = int(x2)
            c = int(x3)

    assign = [-1] * 16
    for _ in range(16):
        for o, poss in possible.items():
            if len(poss) == 1:
                posse = list(poss)[0]
                assign[o] = posse
                for oo in range(16):
                    possible[oo].discard(posse)

    registers = [0] * 4
    for line in part2.strip().splitlines():
        x0, x1, x2, x3 = line.split(" ")
        o = int(x0)
        a = int(x1)
        b = int(x2)
        c = int(x3)
        f = functions[assign[o]]
        registers[c] = f(registers, a, b)

    return registers[0]
