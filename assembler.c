/*processing file and creating the outputs files*/
/*TODO: consider renaming to fileReader*/
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
        int current;
        int afterWord;
        char *firstWord;
        char *secondWord;
        int tempError = 0;
        current = skipTabsAndSpaces(0, line);
        /*if line is comment skip to the next line*/
        if (current == COMMENT_SPECIFIER)
        {
            continue;
        }
        afterWord = getWordLength(current, line);
        firstWord = subString(current, afterWord, line);
        /*if the first word is tag check that is valid and save it as temp*/
        if (firstWord[strlen(firstWord) - 1] == TAG_SPECIFIER)
        {
            addtempTag(firstWord, lineCounter, &tempError, 1);
            if (tempError == ERROR)
            {
                error = ERROR;
                continue;
            }
        }
        /*if the first word is instruction read it and move to the next line*/
        else if (firstWord[0] == INSTRUCTION_SPECIFIER)
        {
            readInstruction(firstWord, current, line, lineCounter, &error);
        }
        /*if the first word is not instruction and not tag it is command.
         read the command and then move to the next line*/
        else
        {
            readCommand(line, firstWord, afterWord, lineCounter, &error);
            continue;
        }

        /*if the code reaches here it means that the first word is tag*/
        current = skipTabsAndSpaces(afterWord, line);
        /*if reached end of line print error*/
        if (checkEndOfLine(current, line))
        {
            error = ERROR;
            printf("Error: line %d, line must contain command or instruction");
            continue;
        }
        afterWord = skipWord(current, line);
        secondWord = subString(current, afterWord, line);
        /* if the second word is instruction read it and move to the next line*/
        if (secondWord[0] == INSTRUCTION_SPECIFIER)
        {
            readInstruction(secondWord, current, line, lineCounter, &error);
            continue;
        }
        /* if the second word is not instruction it is command, read it and move to the next line*/
        else
        {
            readCommand(line, firstWord, afterWord, lineCounter, &error);
            continue;
        }
        lineCounter++;
    }
    /* iteration 2 here*/
}

/*read instruction by letting readEInstruction or readAllocationInstruction to handle it */
static void readInstruction(char *instruction, int afterInstruction, char *line, int currentLine, int *error)
{
    /* if the instruction is external or entry read the instruction*/
    if (instruction[1] == 'e')
    {
        readEInstruction(line, instruction, afterInstruction, currentLine, error);
    }
    /*if the instruction is data read it*/
    else if (instruction[1] == 'd')
    {
        readDataInstruction(line, instruction, afterInstruction, currentLine, error);
    }
    /*if the instruction is string read it*/
    else if (instruction[1] == 's')
    {
        readStringInstruction(line, instruction, afterInstruction, currentLine, error);
    }
    else
    {
        printf("Error: line %d,instruction name is not valid", currentLine);
        (*error) = ERROR;
        return;
    }
}

/*read e instruction (entry or external) - divide it to words and let instructions handler to handle it.
 change error to ERROR if syntex error accrued */
static int readEInstruction(char *line, char *instruction, int afterInstruction, int currentLine, int *error)
{
    char *param;
    int current;
    int currentError = 0;

    /*entry and external should ignore tags*/
    removeTempTag();
    /*extract the paramter of the instruction from the line*/
    current = skipTabsAndSpaces(afterInstruction, line);
    param = readWordParam(line, current, currentLine, &currentError, 0);
    if (!currentError)
    {
        addEInstruction(instruction, param, currentLine, error);
    }
    else
    {
        (*error) = currentError;
    }
}

/* read data instruction - calculate the parameters and let instructions handler to handle it, 
 change error to ERROR if syntex error accrued  */
static void readDataInstruction(char *line, char *instruction, int afterInstruction, int currentLine, int *error)
{
    int params[MAX_LINE_LENGTH];
    int numberOfParams = 1;
    char *paramString;
    int paramInt;
    int current = afterInstruction;
    int afterWord;
    int afterComma;
    int finished = 0;
    /*making the temporary instruction parmenant becuase it will be used*/
    makeTempTagPermanent(getInstructionsWordsCount(), 1, 0, 0);
    /*add all parameters to the list*/
    while (!checkEndOfLine(current, line))
    {
        current = skipTabsAndSpaces(current, line);
        /*if the comma was the last character the program was already exit the loop because find comma stop at the end of the line.
        So when after skipping tabs and spaces end of the line reached but it wasent reached before tabs end spaces
        indicate that ther is extraneous comma after the commandList*/
        if (checkEndOfLine(current, line))
        {
            printf("Error:line %d, extraneous comma after parameters list", line);
            (*error) = ERROR;
            return;
        }
        afterComma = skipComma(current, line);
        afterWord = skipWord(current, line);
        paramString = subString(current, min(afterComma - 1, afterWord), line);
        paramInt = atoi(paramString);
        /* if the parmater is zeo ther are two options:
         or it really is is zero or that atoi was returning zero because it is not a number*/
        if (paramInt == 0)
        {
            if (!checkIfZero(paramString))
            {
                printf("Error: line %d, .data should receive only whole numbers", currentLine);
                (*error) = ERROR;
                return;
            }
        }
        params[numberOfParams] = paramInt;
        current = afterWord;
        numberOfParams++;
    }
    /*there is an edge case in which the end of the line comes right after the comma in which the loop will not notice that*/
    if (line[current - 1] == ',')
    {
        printf("Error:line %d, extraneous comma after parameters list", line);
        (*error) = ERROR;
        return;
    }
    addDataInstruction(instruction, params, numberOfParams, currentLine, *error);
}

/* read string instruction - calculate the parameters and let instructions handler to handle it, 
 change error to ERROR if syntex error accrued  */
static int readStringInstruction(char *line, char *instruction, int afterInstruction, int currentLine, int *error)
{
    char *param;
    int current;
    int currentError = 0;
    /*making the temporary instruction parmenant becuase it will be used*/
    makeTempTagPermanent(getInstructionsWordsCount(), 1, 0, 0);

    /*extract the paramter of the instruction from the line*/
    current = skipTabsAndSpaces(afterInstruction, line);
    param = readWordParam(line, current, currentLine, &currentError, 0);
    if (!currentError)
    {
        addEInstruction(instruction, param, currentLine, error);
    }
    else
    {
        (*error) = currentError;
    }
}
/*read command - divide it to words and let command handler to handle it */
static void readCommand(char *line, char *command, int afterCommand, int currentLine, int *error)
{
    char *param1;
    char *param2;
    int current;
    int currentError = 0;
    /*making the temporary instruction parmenant becuase it will be used*/
    makeTempTagPermanent(getInstructionsWordsCount(), 0, 0, 0);
    current = skipTabsAndSpaces(afterCommand, line);
    param1 = readWordParam(line, current, currentLine, currentError, 0);
    if (!currentError)
    {
        param2 = readWordParam(line, current, currentLine, currentError, 1);
        if (!currentError)
        {
            addCommand(command, param1, param2, currentLine, error);
        }
        else
        {
            *error = currentError;
        }
    }
    else
    {
        *error = currentError;
    }
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
static int skipWord(int current, char str[])
{
    while (str[current] != " " && str[current] != "\t" && str[current] != "\n" && str[current] != "\0")
    {
        current++;
    }
    return current;
}

/*return the first index after comma or the last characterOf theLine*/
static int skipComma(int current, char str[])
{
    while (str[current] != ',' && !checkEndOfLine(current, str))
    {
        current++;
    }
    return current + 1;
}

/*check if reached the end of the line*/
static int checkEndOfLine(int current, char *str)
{
    return str[current] == '\n' || str[current] == '\0';
}

/*check if string represent the number zero ,  if string is empty return 0*/
static int checkIfZero(char *zeroStr)
{
    int i = 0;
    int zero = 1;
    int length = strlen(zeroStr);
    if (length == 0)
    {
        return 0;
    }

    zero &= zeroStr[0] == '-' || zeroStr[0] == '+' || zeroStr[0] == '0';
    for (i = 0; i < length; i++)
    {
        zero &= zeroStr[i] == '0';
    }
    return zero;
}

/*reading paramter that is a whole word, changing current to be the first after the paramter.
last param should be 1 if this paramter is the last and 0 if isnt */
static char *readWordParam(char *line, int *current, int lineNumber, int *error, int lastParam)
{
    char *param = myStringMalloc(sizeof(char) * MAX_LINE_LENGTH);
    int afterParam;
    int current;
    /*extract the paramter of the instruction from the line*/
    int current = skipTabsAndSpaces(current, line);
    if (checkEndOfLine(current, line))
    {
        printf("Error: line %d, the instruction must receive argument", lineNumber);
        (*error) = ERROR;
        return NULL;
    }
    afterParam = skipWord(current, line);
    if (lastParam)
    {
        current = skipTabsAndSpaces(current, line);
        if (!checkEndOfLine(current, line))
        {
            printf("Error: line %d, Extraneous text after instruction", lineNumber);
            (*error) = ERROR;
            return NULL;
        }
    }
    (*current) = afterParam;
    return param;
}
