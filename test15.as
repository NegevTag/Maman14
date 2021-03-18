;checking relative addresing to extern variable and entry and
;extern parameters invalid
;output should be error in line15 and line 14 , line 25 line 26
.entry LIST
.extern W
MAIN: add r3, LIST
LOOP: prn #48
 lea W, r6
 inc r6
 mov r3, K
 sub r1, r4
 bne END
 cmp K, #-6
 bne %W
 dec W
.entry W
 jmp %LOOP
 add L3, L3
END: stop
STR: .string "abcd"
LIST: .data 6, -9
 .data -100
K: .data 31
.extern L3 
.extern r4
.entry @s