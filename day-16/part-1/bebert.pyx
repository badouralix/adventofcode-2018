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
    cdef int i, res
    cdef bint ok

    cdef int a = 0
    cdef int b = 0
    cdef int c = 0

    cdef int count3 = 0
    cdef int count3_inner = 0

    cdef int before[4]
    cdef int after[4]
    for i in range(4):
        before[i] = 0
        after[i] = 0

    cdef int state = 0

    for line in s.splitlines():
        # Before line
        if line.startswith("B"):
            state = 1
            x0, x1, x2, x3 = line.split("[")[1].strip("\n\r ]").split(",")
            before[0] = int(x0)
            before[1] = int(x1)
            before[2] = int(x2)
            before[3] = int(x3)

        # After line
        elif line.startswith("A"):
            state = 3
            x0, x1, x2, x3 = line.split("[")[1].strip("\n\r ]").split(",")
            after[0] = int(x0)
            after[1] = int(x1)
            after[2] = int(x2)
            after[3] = int(x3)

        # Blank line, run ongoing test
        elif line.strip() == "":
            if state == 0:
                return count3

            state = 0
            count3_inner = 0
            for f in functions:
                res = f(before, a, b)
                ok = True
                for i in range(4):
                    if i == c:
                        if res != after[i]:
                            ok = False
                            break
                    else:
                        if before[i] != after[i]:
                            ok = False
                            break
                if ok:
                    count3_inner += 1
            if count3_inner >= 3:
                count3 += 1

        # Operation line
        else:
            state = 2
            x0, x1, x2, x3 = line.split(" ")
            a = int(x1)
            b = int(x2)
            c = int(x3)

    return 0
