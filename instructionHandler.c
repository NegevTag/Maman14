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
static struct entry
{
    char *label;
    int lineNum;
};

/*TODO: make al files more readable (statics done, struct up, functions up)*/
static struct entry(*entryList);

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
    /*if instruction is extern add param to labels*/
    if (strcmp(instruction, ".extern") == 0)
    {
        int tempError = 0;
        addLabel(param, 0, 0, 1, 1, 0, lineNumber, error);
        return;
    }
    /*if instruction is entry add the param to tenterylist*/
    else if (strcmp(instruction, ".entry") == 0)
    {
        if (!isValidLabel(param, 0))
        {
            printf("Error: line %d, invalid label", lineNumber);
            (*error) = ERROR;
            return;
        }
        else
        {
            addEntry(instruction,lineNumber);
        }
    }
    /*if the instruction is not valid print error*/
    else
    {
        printf("Error:line %d, Instruction isn't valid", lineNumber);
        (*error) = ERROR;
        return;
    }
}


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
        if (isValidNumber(params[i]))
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
    /*checking that the instruction is valid*/
    if (strcmp(".string", instruction) != 0)
    {
        printf("Error:line %d, Instruction isn't valid", lineNumber);
        (*error) = ERROR;
        return;
    }
    /*check that the last and first characters are*/
    if ((param[0] != STRING_SPECIFIER) || param[strlen(param) - 1] != STRING_SPECIFIER)
    {
        printf("Error: line %d, String must include \" at the start and \" at the end", lineNumber);
        (*error) = ERROR;
        return;
    }
    /*adding all the as there asci representative numbers*/
    /*not including the first and last characters because they are "*/
    for (i = 1; i < length - 1; i++)
    {
        c = param[i];
        addWordNumber(c);
    }
    /*add the end of the string*/
    addWordNumber('\0');
}

/*adding word that represent number*/
static void addWordNumber(int num)
{
    addWord( num, us_binary_to_int("100"));
}
/*adding word by adress and machineCode and ARE*/
static void addWord(int machineCode, int ARE)
{
    instructionWords[instructionWordsCounter].address = instructionWordsCounter;
    instructionWords[instructionWordsCounter].machineCode = machineCode;
    instructionWords[instructionWordsCounter].ARE = ARE;
    instructionWordsCounter++;
}
/*initialize the instruction*/
void initializeInstruction()
{
    entryList = (struct entry *)(myMalloc(sizeof(struct entry)));
}
/*TODO: rename all lines to line numbers*/
/*add entry to the entry list*/
static void addEntry(char *label,int lineNumber)
{
    /*allocate new memory for the entryList*/
    entryList = (struct entry *)myRealloc(entryList, (entryIndex + 2) * sizeof(struct entry));
    /*add entry to the list*/
    entryList[entryIndex].lineNum = lineNumber;
    /*there is no need to allocate memory for the string because substring allocate memory*/
    entryList[entryIndex].label = label;
    entryIndex++;
}