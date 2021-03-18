;checking space after %,
;no parameters for command only one paramter while should accept 2,
;invalid instruction and command name and externous text after end
;error in line 18 11 12 9 17 23 8 7 19 22
.entry LIST
.extern W
$MAIN: add r3, LIST
LOOP: pr #48
 lea W
 inc r6
 mov 
 sub r1,
 bne END
 cmp K, #-6
 bne %END
 dec W
.entryyy MAIN
 jmp % LOOP
 add L3, L3 abcdsdsa
END: stop
STR: .string "abcd"
LIST: .data 6, -9,000abc
 .dataaa -100
K: .data 31
.extern L3 