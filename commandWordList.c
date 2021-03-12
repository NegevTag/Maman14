/*data structare for the words that represent commands in the machineCode*/
#include "header.h"
/*represent word of code*/
struct wordCommand
{
    /*TODO:consider changing the label by creating array of labels and indexes and lines*/
    unsigned int address;
    unsigned int machineCode : 12;
    unsigned int ARE : 3;
};

static int commandWordsCounter = 0;

/*the commands in the memory*/
static struct wordCommand commandWordList[MEMORY_SIZE];
/*add command word to the command word list, return ERROR if error occurred*/
int addCommandWord(int machineCode, int ARE)
{
    if (commandWordsCounter >= MEMORY_SIZE)
    {
        return ERROR;
    }
    commandWordList[commandWordsCounter].address = FIRST_ADDRESS + commandWordsCounter;
    commandWordList[commandWordsCounter].machineCode = machineCode;
    commandWordList[commandWordsCounter].ARE = ARE;
    commandWordsCounter++;
    return 0;
}
/*return the number of commandwords*/
int getNumberOfCommandWords(){
    return commandWordsCounter;
}
/*get the address of the next command*/
int getNextcommandWordAddress(){
    return commandWordsCounter + FIRST_ADDRESS;
}