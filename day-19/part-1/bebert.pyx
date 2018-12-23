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


functions = {"addr": addr, "addi": addi, "mulr": mulr, "muli": muli,
             "banr": banr, "bani": bani, "borr": borr, "bori": bori,
             "setr": setr, "seti": seti, "gtir": gtir, "gtri": gtri,
             "gtrr": gtrr, "eqir": eqir, "eqri": eqri, "eqrr": eqrr}


cpdef int run(s):
    cdef int ipb = 0
    cdef int ip = 0
    cdef int i
    cdef int a
    cdef int b
    cdef int c

    cdef int registers[6]
    for i in range(6):
        registers[i] =  0

    instructions = []

    for line in s.splitlines():
        if line.startswith("#ip "):
            ipb = int(line[4:])
            continue

        x0, x1, x2, x3 = line.split(" ")
        instructions.append((x0, int(x1), int(x2), int(x3)))

    cdef int n = len(instructions)

    # print("ip:", ip)
    # print("ipb:", ipb)
    # print("instructions:", instructions)
    # print("n:", n)

    while ip < n:
        x0, a, b, c = instructions[ip]
        registers[ipb] = ip

        f = functions[x0]

        registers[c] = f(registers, a, b)
        ip = registers[ipb]
        ip += 1

    return registers[0]
