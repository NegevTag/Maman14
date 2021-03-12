/*represent the words that represent commands in the machineCode*/
/*not responsible for printing error messeges if accures*/
#include "header.h"
#include "commandsHeader.h"
/*represent word of code*/
struct wordCommand
{
    /*TODO:consider changing the label by creating array of labels and indexes and lines*/
    unsigned int address;
    unsigned int machineCode : 12;
    unsigned int ARE : 3;
};

static int commandWordsCounter = 0;

static struct wordCommand commandWordList[MEMORY_SIZE];
/*add command word to the command word list, change error to ERROR if error occurred*/
void addCW(int machineCode, int ARE, int *error)
{
    if (commandWordsCounter >= MEMORY_SIZE)
    {
        (*error) = ERROR;
        return;
    }
    commandWordList[commandWordsCounter].address = FIRST_ADDRESS + commandWordsCounter;
    commandWordList[commandWordsCounter].machineCode = machineCode;
    commandWordList[commandWordsCounter].ARE = ARE;
    commandWordsCounter++;
}
/*return the number of commandwords*/
int getNumberOfCW()
{
    return commandWordsCounter;
}
/*get the address of the next command word*/
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
/*check if adress is valid*/
static int isValidAddress(int address)
{
    return address >= FIRST_ADDRESS && address < commandWordsCounter + FIRST_ADDRESS;
}