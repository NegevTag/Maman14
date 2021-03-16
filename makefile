prog: commandHandler.o commandList.o commandWordList.o labelParamsList.o instructionHandler.o entryList.o instructionWordsList.o labelHandler.o assembler.o utilities.o main.o

	gcc -g -ansi -Wall -pedantic commandHandler.o commandList.o commandWordList.o labelParamsList.o instructionHandler.o entryList.o instructionWordsList.o labelHandler.o assembler.o utilities.o main.o -o prog 



commandHandler.o: commandHandler.c projectHeader.h commandsHeader.h

	gcc -c -ansi -Wall -pedantic commandHandler.c -o commandHandler.o 

commandList.o: commandList.c projectHeader.h commandsHeader.h

	gcc -c -ansi -Wall -pedantic commandList.c -o commandList.o 

commandWordList.o: commandWordList.c projectHeader.h commandsHeader.h 

	gcc -c -ansi -Wall -pedantic commandWordList.c -o commandWordList.o

labelParamsList.o: labelParamsList.c projectHeader.h commandsHeader.h 

	gcc -c -ansi -Wall -pedantic labelParamsList.c -o labelParamsList.o 





instructionHandler.o: instructionHandler.c projectHeader.h instructionHeader.h

	gcc -c -ansi -Wall -pedantic instructionHandler.c -o instructionHandler.o 

entryList.o: entryList.c projectHeader.h instructionHeader.h

	gcc -c -ansi -Wall -pedantic entryList.c -o entryList.o 

instructionWordsList.o: instructionWordsList.c projectHeader.h instructionHeader.h

	gcc -c -ansi -Wall -pedantic instructionWordsList.c -o instructionWordsList.o 



labelHandler.o: labelHandler.c projectHeader.h

	gcc -c -ansi -Wall -pedantic labelHandler.c -o labelHandler.o 

assembler.o: assembler.c projectHeader.h

	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o 

utilities.o: utilities.c projectHeader.h

	gcc -c -ansi -Wall -pedantic utilities.c -o utilities.o 

main.o: main.c projectHeader.h

	gcc -c -ansi -Wall -pedantic main.c -o main.o

debugable: commandHandler.c commandList.c commandWordList.c labelParamsList.c instructionHandler.c entryList.c instructionWordsList.c labelHandler.c assembler.c utilities.c main.c

	gcc -g -ansi -Wall -pedantic commandHandler.c commandList.c commandWordList.c labelParamsList.c instructionHandler.c entryList.c instructionWordsList.c labelHandler.c assembler.c utilities.c main.c -o debugable 







