        seti 123 0 3            $3 := 123
check:  bani 3 456 3            $3 &= 456
        eqri 3 72 3             $3 := $3 == 72
        addr 3 2 2              ip += $3
        seti 0 0 2              goto check
        seti 0 4 3              $3 := 0
loop:   bori 3 65536 4          $4 := $3 | 65536
        seti 1107552 3 3        $3 := 1107552
set_5:  bani 4 255 5            $5 := $4 & 255
        addr 3 5 3              $3 += $5
        bani 3 16777215 3       $3 := $3 & 16777215
        muli 3 65899 3          $3 *= 65899
        bani 3 16777215 3       $3 := $3 & 16777215
        gtir 256 4 5            $5 := $4 < 256      if d < 256:
        addr 5 2 2              ip += $5                goto end
        addi 2 1 2              ip += 1
        seti 27 0 2             goto end
        seti 0 2 5              $5 := 0             e = 0
test_1: addi 5 1 1              $1 := $5 + 1        a = e + 1
        muli 1 256 1            $1 *= 256
        gtrr 1 4 1              $1 := $1 > $4       if a > d:
        addr 1 2 2              ip += $1                d = e
        addi 2 1 2              ip += 1                 goto set_5
        seti 25 3 2             goto set_4
        addi 5 1 5              $5 += 1             e += 1
        seti 17 3 2             goto test_1
set_4:  setr 5 3 4              $4 := $5
        seti 7 4 2              goto set_5
end:    eqrr 3 0 5              $5 := $3 == $0      if c == x:
        addr 5 2 2              ip += $5                exit
        seti 5 8 2              goto loop