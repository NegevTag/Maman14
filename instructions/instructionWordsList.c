/*represent the words that represent instruction in the machineCode*/
/*not responsible for printing error messages if occurs*/
#include "header.h"
struct wordInstruction
{
    /*TODO: explain ARE*/
    unsigned int address;
    unsigned int machineCode : 12;
    unsigned int ARE : 3;
};

static struct wordInstruction instructionWords[MEMORY_SIZE];
static int instructionWordsCounter = 0;
/*adding word by adress and machineCode and ARE*/
static void addWord(int machineCode, int ARE)
{
    instructionWords[instructionWordsCounter].address = instructionWordsCounter;
    instructionWords[instructionWordsCounter].machineCode = machineCode;
    instructionWords[instructionWordsCounter].ARE = ARE;
    instructionWordsCounter++;
}

