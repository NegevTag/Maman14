/*handling all the instructions (hanchiot)*/
#include "header.h"

/* get all the words in the output format*/
char *getinstructionsWordsList()
{
}
/* update all the entry instructions, and creating the .ent output file*/
void updateEntryInstructions(char *fileName, int *error)
{
    int lineNum;
    char *entryLabel;
    int entryLabelAddress;
    int i = 0;
    FILE *f = fopen(strcat(fileName, ".en"), 'w');
    if (!f)
    {
        printf("Error: could not open file\n", fileName);
        (*error) = ERROR;
        return;
    }
    /*make all entry label entry and add them to the list*/
    while ((entryLabel = getEntryLabel(i, &lineNum)) != '\0')
    {
        entryLabelAddress = setEntry(entryLabel, lineNum, error);
        if ((*error) != ERROR)
        {
            /*add the entry label to the file*/
            fprintf(f, "%s %d", entryLabel, lineNum);
        }
    }
    fclose(f);
    /*if error accrued delete the file*/
    if ((*error) ==ERROR)
    {
        remove(strcat(fileName, ".en"));
    }

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
    /*if instruction is entry add the param to to enterylist*/
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
            addEntry(instruction, lineNumber);
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
    addWord(num, us_binary_to_int("100"));
}

/*TODO: rename all lines to line numbers*/
