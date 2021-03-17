/*handling all the instructions (hanchiot)*/
#include "projectHeader.h"
#include "instructionHeader.h"

static void addWordNumber(int num);
/* update all the entry instructions, and creating the .ent output file*/
void updateEntryInstructions(char *fileName, int *error)
{
    int lineNum;
    char *entryLabel;
    int entryLabelAddress;
    int i = 0;
    int emptyFile = 1;
    char enName[MAX_FILE_NAME_LENGTH + 4];
    FILE *f;
    strcpy(enName, fileName);
    strcat(enName,".ent");
    f = fopen(enName, "wt");
    if (!f)
    {
        printf("Error: could not open file\n");
        (*error) = ERROR;
        return;
    }
    /*make all entry label entry and add them to the list*/
    while ((entryLabel = getEntryLabel(i, &lineNum)) != NULL)
    {
        entryLabelAddress = setEntry(entryLabel, lineNum, error);
        if ((*error) != ERROR)
        {
            /*add the entry label to the file*/
            fprintf(f, "%s %d\n", entryLabel, entryLabelAddress);
            emptyFile = 0;
        }
        i++;
    }
    fclose(f);
    /*if error accrued or the file is empty delete the file*/
    if ((*error) == ERROR || emptyFile)
    {
        remove(enName);
    }
}
/*append instruction to the output file*/
void appendInstructionToOutput(char *fileName, int *error)
{
    int i;
    char obName[MAX_FILE_NAME_LENGTH + 3];
    FILE *ob;
    strcpy(obName,fileName);
    strcat(obName,".ob");
    ob = fopen(obName, "at");
    if ((*error) != ERROR)
    {

        if (!ob)
        {
            printf("Error: could not open file\n");
            (*error) = ERROR;
            return;
        }
        for (i = 0; i < getNumberOfIW(); i++)
        {

            addIWRepresentativeStringToFile(ob, i);
        }
    }
}
/*adding e instruction (entry or external) the instruction*/
void addEInstruction(char *instruction, char *param, int lineNum, int *error)
{
    /*if instruction is extern add param to labels*/
    if (strcmp(instruction, ".extern") == 0)
    {
        addLabel(param, 0, 0, 1, 1, 0, lineNum, error);
        return;
    }
    /*if instruction is entry add the param to to enterylist*/
    else if (strcmp(instruction, ".entry") == 0)
    {
        if (!isValidLabel(param, 0, 1))
        {
            printf("Error: line %d, invalid label\n", lineNum);
            (*error) = ERROR;
            return;
        }
        else
        {
            addEntry(param, lineNum);
        }
    }
    /*if the instruction is not valid print error*/
    else
    {
        printf("Error:line %d, Instruction isn't valid\n", lineNum);
        (*error) = ERROR;
        return;
    }
}

void addDataInstruction(char *instruction, int params[], int numberOfParams, int lineNum, int *error)
{
    int i;
    /*checking that the instruction is correct*/
    if (strcmp(".data", instruction) != 0)
    {
        printf("Error:line %d, Instruction isn't valid\n", lineNum);
        (*error) = ERROR;
        return;
    }
    /*checking that the parameters are correct*/
    for (i = 0; i < numberOfParams; i++)
    {
        if (!isValidNumber(params[i]))
        {
            printf("Error: line %d, number is out of limits\n", lineNum);
            (*error) = ERROR;
            return;
        }
        addWordNumber(params[i]);
    }
}
/* add the string instruction (and checking that it is string instruction)*/
void addStringInstruction(char *instruction, char *param, int lineNum, int *error)
{
    int i;
    int length = strlen(param);
    int c;
    /*checking that the instruction is valid*/
    if (strcmp(".string", instruction) != 0)
    {
        printf("Error:line %d, Instruction isn't valid\n", lineNum);
        (*error) = ERROR;
        return;
    }
    /*check that the last and first characters are*/
    if ((param[0] != STRING_SPECIFIER) || param[strlen(param) - 1] != STRING_SPECIFIER)
    {
        printf("Error: line %d, String must include \" at the start and \" at the end\n", lineNum);
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
