/*handling all the instructions (hanchiot)*/
#include "header.h"

/*TODO: consider split to two files*/
struct wordInstruction
{
    /*TODO: explain ARE*/
    /*TODO:consider changing the label by creating array of labels and indexes and lines*/
    unsigned int address;
    unsigned int machineCode : 12;
    unsigned int ARE : 3;
};

static struct wordInstruction instructionWords[MEMORY_SIZE];
static int instructionWordsCounter = 0;
static char** entryList;
static int entryIndex = 0;
/* get all the words in the output format*/
char *getinstructionsWordsList()
{
}
/* update all the addresses of the instructions for iteration2*/
void updateInstructions()
{
    /* update adresses*/
    /*update internal*/
}
int getInstructionsWordsCount()
{
}
/*adding e instruction (entry or external) the instruction*/
void addEInstruction(char *instruction, char *param, int lineNumber, int *error)
{
    if (strcmp(instruction, ".extern") == 0)
    {
        int tempError = 0;
        addTag(param, 0, 0, 1, 1, 0, lineNumber, error);
        return;
    }
    else if (strcmp(instruction, ".entry") == 0)
    {
        if (!isValidTag(param,0))
        {
           printf("Error: line %d, invalid tag",lineNumber);
           (*error) = ERROR;
           return;
        }else{
            entryList[entryIndex] = param;
            entryIndex++;
        }
        
    }
    else
    {
        printf("Error:line %d, Instruction isn't valid", lineNumber);
        (*error) = ERROR;
        return;
    }

    /* if instruction is data or string add params to code*/
    /*if instruction is extrnal read params[0] and add it to the tags*/
    /*if instruction is is internal read params[0] and add it to the internal list*/
}
/*TODO: check if it is not better to implement without array*/
/* add the data instruction (and checking that it is data)*/
void addDataInstruction(char *instruction, int params[], int numberOfParams, int lineNumber, int *error)
{
    int i;
    /*checking that the instruction is correct*/
    if (strcmp(".data", instruction) != 0)
    {
        printf("Error:line %d, Instruction isn't valid", lineNumber);
        (*error) = ERROR;
        return;
    }
    /*checking that the parameters are correct*/
    for (i = 0; i < numberOfParams; i++)
    {
        if (params[i] > MAX_NUMBER || params[i] < MIN_NUMBER)
        {
            printf("Error: line %d, number is out of limits", lineNumber);
            (*error) = ERROR;
            return;
        }
        else
        {
            addWordNumber(params[i]);
        }
    }
}
/* add the string instruction (and checking that it is string instruction)*/
void addStringInstruction(char *instruction, char *param, int lineNumber, int *error)
{
    int i;
    int length = strlen(param);
    int c;
    if (strcmp(".string", instruction) != 0)
    {
        printf("Error:line %d, Instruction isn't valid", lineNumber);
        (*error) = ERROR;
        return;
    }
    if ((param[0] != STRING_SPECIFIER) || param[strlen(param) - 1] != STRING_SPECIFIER)
    {
        printf("Error: line %d, String must include \" at the start and \" at the end", lineNumber);
        (*error) = ERROR;
        return;
    }
    /*not including the first and last characters because they are "*/
    for (i = 1; i < length - 1; i++)
    {
        c = param[i];
        addWordNumber(c);
    }
    /*add the end of the string*/
    addWordNumber('\0');
}
static void addWordNumber(int num)
{
    addWord(instructionWordsCounter, num, 4);
}
static void addWord(int address, int machineCode, int ARE)
{
    instructionWords[instructionWordsCounter].address = address;
    instructionWords[instructionWordsCounter].machineCode = machineCode;
    instructionWords[instructionWordsCounter].ARE = ARE;
    instructionWordsCounter++;
}
