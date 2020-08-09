        addi 1 16 1 GOTO jmp
start:  seti 1 4 2  $2 = 1
        seti 1 0 3  $3 = 1      // On entry: a = 0, b = 1, c = 1, d = 0, e = 10551296
begin:  mulr 2 3 4  $4 = $2 * $3    // while c <= e:
        eqrr 4 5 4  $4 = $4 == $5   //   if b * c == e:
        addr 4 1 1  ip += $4
        addi 1 1 1  GOTO endif
        addr 2 0 0  $0 += $2        //     a += b
endif:  addi 3 1 3  $3++            //   c++
        gtrr 3 5 4  $4 = $3 > $5
        addr 1 4 1  ip += $4
        seti 2 4 1  GOTO begin
        addi 2 1 2  $2++
        gtrr 2 5 4  $4 = $2 > $5
        addr 4 1 1  ip += $4
        seti 1 1 1  GOTO start + 1
        mulr 1 1 1  EXIT
jmp:    addi 5 2 5  $5 += 2
        mulr 5 5 5  $5 *= $5
        mulr 1 5 5  $5 *= 19
        muli 5 11 5 $5 *= 11
        addi 4 2 4
        mulr 4 1 4
        addi 4 16 4
        addr 5 4 5
        addr 1 0 1  ip += $0
        seti 0 7 1  GOTO start
        setr 1 5 4
        mulr 4 1 4
        addr 1 4 4
        mulr 1 4 4
        muli 4 14 4
        mulr 4 1 4
        addr 5 4 5
        seti 0 9 0  $0 = 0
        seti 0 4 1  GOTO start