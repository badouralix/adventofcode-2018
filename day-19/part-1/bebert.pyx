cdef void addr(int *reg, int a, int b, int c):
    reg[c] = reg[a] + reg[b]

cdef void addi(int *reg, int a, int b, int c):
    reg[c] = reg[a] + b

cdef void mulr(int *reg, int a, int b, int c):
    reg[c] = reg[a] * reg[b]

cdef void muli(int *reg, int a, int b, int c):
    reg[c] = reg[a] * b

cdef void banr(int *reg, int a, int b, int c):
    reg[c] = reg[a] & reg[b]

cdef void bani(int *reg, int a, int b, int c):
    reg[c] = reg[a] & b

cdef void borr(int *reg, int a, int b, int c):
    reg[c] = reg[a] | reg[b]

cdef void bori(int *reg, int a, int b, int c):
    reg[c] = reg[a] | b

cdef void setr(int *reg, int a, int b, int c):
    reg[c] = reg[a]

cdef void seti(int *reg, int a, int b, int c):
    reg[c] = a

cdef void gtir(int *reg, int a, int b, int c):
    if a > reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0

cdef void gtri(int *reg, int a, int b, int c):
    if reg[a] > b:
        reg[c] = 1
    else:
        reg[c] = 0

cdef void gtrr(int *reg, int a, int b, int c):
    if reg[a] > reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0

cdef void eqir(int *reg, int a, int b, int c):
    if a == reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0

cdef void eqri(int *reg, int a, int b, int c):
    if reg[a] == b:
        reg[c] = 1
    else:
        reg[c] = 0

cdef void eqrr(int *reg, int a, int b, int c):
    if reg[a] == reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0


functions_map = {"addr":  0, "addi":  1, "mulr":  2, "muli":  3,
                 "banr":  4, "bani":  5, "borr":  6, "bori":  7,
                 "setr":  8, "seti":  9, "gtir": 10, "gtri": 11,
                 "gtrr": 12, "eqir": 13, "eqri": 14, "eqrr": 15}


cdef (void (int *, int, int, int)) *functions[16]
functions[:] = [addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr]


cdef struct Instruction:
    unsigned char fi
    unsigned char a
    unsigned char b
    unsigned char c


cpdef int run(s):
    cdef int ipb = 0
    cdef int ip = 0
    cdef int i
    cdef Instruction ins

    cdef int registers[6]
    for i in range(6):
        registers[i] = 0

    cdef Instruction instructions[1000]

    cdef int n_instructions = 0
    for line in s.splitlines():
        if line.startswith("#ip "):
            ipb = int(line[4:])
            continue

        x0, x1, x2, x3 = line.split(" ")
        instructions[n_instructions] = Instruction(fi=functions_map[x0], a=int(x1), b=int(x2), c=int(x3))
        n_instructions += 1

    # print("ip:", ip)
    # print("ipb:", ipb)
    # print("instructions:", instructions)
    # print("n:", n)

    while ip < n_instructions:
        ins = instructions[ip]
        registers[ipb] = ip

        functions[ins.fi](registers, ins.a, ins.b, ins.c)
        ip = registers[ipb]
        ip += 1

    return registers[0]
