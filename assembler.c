/*processing file and creating the outputs files*/
#include "header.h"
#define ERROR 1
void process(FILE *f)
{
    /*if error == 1 then error has accrued*/
    int error = 0;
    char line[MAX_LINE_LENGTH];
    int lineCounter = 1;
    while (fgets(line, MAX_LINE_LENGTH, f))
    {
        int current = 0;
        int afterWord;
        char *firstWord;
        char *secondWord;
        current = skipTabsAndSpaces(0, line);
        /*if line is comment skip to the next line*/
        if (current == COMMENT_SPECIFIER)
        {
            continue;
        }
        afterWord = getWordLength(current, line);
        firstWord = subString(current, afterWord, line);
        /* if there is a problem in memory allocation stop handling this file*/
        if (firstWord == NULL)
        {
            return;
        }
        /*if the first word is tag check that is valid and save it as temp*/
        if (firstWord[strlen(firstWord) - 1] == TAG_SPECIFIER)
        {
            if (!validTag(firstWord))
            {
                error = ERROR;
                printf("Error: line %d, tag name is not valid", lineCounter);
                continue;
            }
            else
            {
                addTempTag(firstWord);
            }
        }
        /*if the first word is instruction read it and move to the next line*/
        else if (firstWord[0] == INSTRUCTION_SPECIFIER)
        {
            readInstruction(firstWord, current, line);
        }
        /*if the first word is not instruction and not tag it is command.
         read the command and then move to the next line*/
        else
        {
            readCommand(line, firstWord, afterWord);
            continue;
        }

        /*if the code reaches here it means that the first word is tag*/
        current = skipTabsAndSpaces(afterWord, line);
        /*if reached end of line*/
        if (line[current] == '\0' || line[current] == '\n')
        {
            error = ERROR;
            printf("Error: line %d, line must contain command or instruction");
            continue;
        }
        afterWord = getCharAfterWord(current, line);
        secondWord = subString(current, afterWord, line);
        /* if there is a problem in memory allocation stop handling this file*/
        if (secondWord == NULL)
        {
            return;
        }
        /* if the second word is instruction read it and move to the next line*/
        if (secondWord[0] == INSTRUCTION_SPECIFIER)
        {
            readInstruction(secondWord, current, line);
            continue;
        }
        /* if the second word is not instruction it is command, read it and move to the next line*/
        else
        {
            readCommand(line, firstWord, afterWord);
            continue;
        }
        lineCounter++;
    }
    /* iteration 2 here*/
}

/*read instruction by letting readEInstruction or readAllocationInstruction to handle it */
static void readInstruction(char *line, char *instruction, int afterInstruction)
{
    /* if the instruction is external or entry read the instruction and move to the next line*/
    if (instruction[1] == 'e')
    {
        readEInstruction(line, instruction, afterInstruction);
    }
    /*if the instruction is data or string read it and then move to the next line*/
    else
    {
        readAllocationInstruction(line, instruction, afterInstruction);
    }
}

/*read e instruction (entry or external) - divide it to words and let instructions handler to handle it */
static void readEInstruction(char *line, char *instruction, int afterInstruction)
{
}
/* read allocation instruction (data or string) - divide it to words and let instructions handler to handle it */
static void readAllocationInstruction(char *line, char *instruction, int afterInstruction)
{
}

/*read command - divide it to words and let command handler to handle it */
static void readCommand(char *line, char *command, int afterCommand)
{
}
/* return the index after tabs and spaces*/
static int skipTabsAndSpaces(int current, char str[])
{
    while (str[current] == '\t' || str[current] == ' ')
    {
        current++;
    }
    return current;
}
/*return the first index after word*/
static int getCharAfterWord(int current, char str[])
{
    int i = current;
    while (str[i] != " " && str[i] != "\t" && str[i] != "\n" && str[i] != "\0")
    {
        i++;
    }
    return i;
}
