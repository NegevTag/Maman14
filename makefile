prog: commandHandler.o commandList.o commandWordList.o labelParamsList.o instructionHandler.o entryList.o instructionWordsList.o labelHandler.o assembler.o utilities.o main.o

	gcc -g -ansi -Wall -pedantic commandHandler.o commandList.o commandWordList.o labelParamsList.o instructionHandler.o entryList.o instructionWordsList.o labelHandler.o assembler.o utilities.o main.o -o prog 2>> errors.txt



commandHandler.o: commandHandler.c projectHeader.h commandsHeader.h

	gcc -c -ansi -Wall -pedantic commandHandler.c -o commandHandler.o 2>> errors.txt

commandList.o: commandList.c projectHeader.h commandsHeader.h

	gcc -c -ansi -Wall -pedantic commandList.c -o commandList.o 2>> errors.txt

commandWordList.o: commandWordList.c projectHeader.h commandsHeader.h 

	gcc -c -ansi -Wall -pedantic commandWordList.c -o commandWordList.o 2>> errors.txt

labelParamsList.o: labelParamsList.c projectHeader.h commandsHeader.h 

	gcc -c -ansi -Wall -pedantic labelParamsList.c -o labelParamsList.o 2>> errors.txt





instructionHandler.o: instructionHandler.c projectHeader.h instructionHeader.h

	gcc -c -ansi -Wall -pedantic instructionHandler.c -o instructionHandler.o 2>> errors.txt

entryList.o: entryList.c projectHeader.h instructionHeader.h

	gcc -c -ansi -Wall -pedantic entryList.c -o entryList.o 2>> errors.txt

instructionWordsList.o: instructionWordsList.c projectHeader.h instructionHeader.h

	gcc -c -ansi -Wall -pedantic instructionWordsList.c -o instructionWordsList.o 2>> errors.txt



labelHandler.o: labelHandler.c projectHeader.h

	gcc -c -ansi -Wall -pedantic labelHandler.c -o labelHandler.o 2>> errors.txt

assembler.o: assembler.c projectHeader.h

	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o 2>> errors.txt

utilities.o: utilities.c projectHeader.h

	gcc -c -ansi -Wall -pedantic utilities.c -o utilities.o 2>> errors.txt

main.o: main.c projectHeader.h

	gcc -c -ansi -Wall -pedantic main.c -o main.o 2>> errors.txt

debugable: commandHandler.c commandList.c commandWordList.c labelParamsList.c instructionHandler.c entryList.c instructionWordsList.c labelHandler.c assembler.c utilities.c main.c

	gcc -g -ansi -Wall -pedantic commandHandler.c commandList.c commandWordList.c labelParamsList.c instructionHandler.c entryList.c instructionWordsList.c labelHandler.c assembler.c utilities.c main.c -o debugable 2>> errors.txt







