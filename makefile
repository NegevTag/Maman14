prog: commndHandler.o commndList.o commndWordList.o labelParamList.o instructionHandler.o entryList.o instructionWordsList.o labelHandler.o assembler.o utilities.o main.o
	gcc -g -ansi -Wall -pedantic commndHandler.o commndList.o commndWordList.o labelParamList.o instructionHandler.o entryList.o instructionWordsList.o labelHandler.o assembler.o utilities.o main.o -o prog

commndHandler.o: commndHandler.c projectHeader.h commandsHeader.h
	gcc -c -ansi -Wall -pedantic commandHandler.c -o commandHandler.h
commndList.o: commndList.c projectHeader.h commandsHeader.h
	gcc -c -ansi -Wall -pedantic commandList.c -o commandList.o 
commndWordList.o: commndWordList.c projectHeader.h commandsHeader.h
	gcc -c -ansi -Wall -pedantic commandWordList.c -o commandWordList.o 
labelParamList.o: labelParamList.c projectHeader.h commandsHeader.h
	gcc -c -ansi -Wall -pedantic labelParamList.c -o labelParamList.o


instructionHandler.o: instructionHandler.c projectHeader.h instructionHeader.h
	gcc -c -ansi -Wall -pedantic instructionHandler.c -o instructionHandler.h
entryList.o: entryList.c projectHeader.h instructionHeader.h
	gcc -c -ansi -Wall -pedantic entryList.c -o entryList.h
instructionWordsList.o: instructionWordsList.c projectHeader.h instructionHeader.h
	gcc -c -ansi -Wall -pedantic instructionWordsList.c -o instructionWordsList.h

labelHandler.o: labelHandler.c projectHeader.h
	gcc -c -ansi -Wall -pedantic labelHandler.c -o labelHandler.h
assembler.o: assembler.c projectHeader.h
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.h
utilities.o: utilities.c projectHeader.h
	gcc -c -ansi -Wall -pedantic utilities.c -o utilities.h
main.o: main.c projectHeader.h
	gcc -c -ansi -Wall -pedantic main.c -o main.h




