; checking instructions without parameters
;output should be  errors in lines 3 and 4 and 19 and 20
.entry
.extern 
MAIN: add r3, LIST
LOOP: prn #48
 lea W, r6
 inc r6
 mov r3, K
 sub r1, r4
 bne END
 cmp K, #-6
 bne %END
 dec W
.entry MAIN
 jmp %LOOP
 add L3, L3
END: stop
STR: .string 
LIST: .data 
 .data -100
K: .data 31
.extern L3 