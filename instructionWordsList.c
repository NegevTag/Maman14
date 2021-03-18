/*represent the words that represent instruction in the machineCode*/
/*not responsible for printing error messages if occurs*/
#include "projectHeader.h"
#include "instructionHeader.h"
struct wordInstruction
{
    unsigned int machineCode : 12;
    unsigned int ARE : 3; /* 001 for E, 010 for R, 100 for A*/
};

static struct wordInstruction instructionWords[MEMORY_SIZE];
static int instructionWordsCounter;

void initializeIWList(){
    instructionWordsCounter = 0;
}
/*adding word by adress and machineCode and ARE*/
void addWord(int machineCode, int ARE)
{
    instructionWords[instructionWordsCounter].machineCode = machineCode;
    instructionWords[instructionWordsCounter].ARE = ARE;
    instructionWordsCounter++;
}
/*add the representative string of the command by the output file format, return ERROR if not valid */
int addIWRepresentativeStringToFile(FILE *f, int index)
{
    if (index >= 0 && index < instructionWordsCounter)
    {
        char ARE = 0;
        if (instructionWords[index].ARE == us_binary_to_int("001"))
        {
            ARE = 'E';
        }
        if (instructionWords[index].ARE == us_binary_to_int("010"))
        {
            ARE = 'R';
        }
        if (instructionWords[index].ARE == us_binary_to_int("100"))
        {
            ARE = 'A';
        }

        fprintf(f, "%04d %03X %c\n", index + getNumberOfCW() + FIRST_ADDRESS, instructionWords[index].machineCode, ARE);
        return 1;
    }
    return ERROR;
}
int getNumberOfIW()
{
    return instructionWordsCounter;
}
