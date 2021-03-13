/*represent the words that represent commands in the machineCode*/
/*not responsible for printing error messeges if accures*/
#include "projectHeader.h"
#include "commandsHeader.h"
static int isValidAddress(int address);

/*represent word of code*/
static struct wordCommand
{
    unsigned int address;
    unsigned int machineCode : 12;
    unsigned int ARE : 3; /* 001 for E, 010 for R, 100 for A*/
};

static int commandWordsCounter = 0;

static struct wordCommand commandWordList[MEMORY_SIZE];
/*add command word to the command word list, return ERROR if error occurred*/
int addCW(int machineCode, int ARE)
{
    if (commandWordsCounter >= MEMORY_SIZE)
    {
        return ERROR;
    }
    commandWordList[commandWordsCounter].address = FIRST_ADDRESS + commandWordsCounter;
    commandWordList[commandWordsCounter].machineCode = machineCode;
    commandWordList[commandWordsCounter].ARE = ARE;
    commandWordsCounter++;
    return 1;
}
/*return the number of commandwords*/
int getNumberOfCW()
{
    return commandWordsCounter;
}
/*get the address of the next command word (that wasent enterd yet*/
int getNextCWAddress()
{
    return commandWordsCounter + FIRST_ADDRESS;
}
/*set the machine code of the command word in specified address, if not found return ERROR else return 1*/
int setCWMachineCode(int address, int machineCode)
{
    if (!isValidAddress(address))
    {
        return ERROR;
    }
    commandWordList[address - FIRST_ADDRESS].machineCode = machineCode;
    return 1;
}
/*get the machine code of the command word in specified address, if not found return ERROR*/
int getCWMachineCode(int address)
{
    if (!isValidAddress(address))
    {
        return ERROR;
    }
    return commandWordList[address - FIRST_ADDRESS].machineCode;
}
/*change command word ARE to E return 1 if worked and error if not*/
int changeCWToExternal(int address)
{
    if (isValidAddress(address))
    {
        commandWordList[address - FIRST_ADDRESS].ARE = us_binary_to_int("001");
        return 1;
    }
    return 0;
}
/*get the representative string of the command by the output file format, return ERROR if not valid */
int addCWRepresentativeStringToFile(FILE *f, int address)
{
    char ARE = 0;
    if (ARE == us_binary_to_int("001"))
    {
        ARE = 'E';
    }
    if (ARE == us_binary_to_int("010"))
    {
        ARE = 'R';
    }
    if (ARE == us_binary_to_int("100"))
    {
        ARE = 'A';
    }

    if (isValidAddress(address))
    {
        fprintf(f, "%d %x %c\n", commandWordList[address - FIRST_ADDRESS].address, commandWordList[address - FIRST_ADDRESS].machineCode, ARE);
        return 1;
    }
    return ERROR;
}
/*check if adress is valid*/
static int isValidAddress(int address)
{
    return address >= FIRST_ADDRESS && address < commandWordsCounter + FIRST_ADDRESS;
}
