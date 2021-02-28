prog: codeInstruaction.o utilities.o 
	gcc -g -ansi -Wall -pedantic utilities.o codeInstruaction.o -o prog
codeInstruaction.o: codeInstruaction.c header.h
	gcc -c -ansi -Wall -pedantic codeInstruaction.c -o codeInstruaction.o 
utilities.o: utilities.c header.h
	gcc -c -ansi -Wall -pedantic utilities.c -o utilities.o 
