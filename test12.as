; checking problemtic labels names
;output should be same as correctOutput but labels name different
.entry R2
.extern r
r9: add r3, R2
LOOP: prn #48
 lea r, r6
 inc r6
 mov r3, K
 sub r1, r4
 bne END
 cmp K, #-6
 bne %END
 dec r
.entry r9
 jmp %LOOP
 add L3, L3
END: stop
STR: .string "abcd"
R2: .data 6, -9
 .data -100
K: .data 31
.extern L3 