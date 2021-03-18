; checking files without spaces
;output should be same as correctOutput except the data instruction
.entry LIST
.extern W
MAIN: add r3, LIST
LOOP: prn #48
 lea W,r6
 inc r6
 mov r3,K
 sub r1,r4
 bne END
 cmp K,#-6
 bne %END
 dec W
.entry MAIN
 jmp %LOOP
 add L3,L3
END: stop
STR: .string "abcd"
LIST: .data 6,-9,0,100,20
 .data -100
K: .data 31
.extern L3 