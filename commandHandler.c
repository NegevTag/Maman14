/* handling all commands (horaa) operations for iteration 1 and 2 */
#include "header.h"
#define ONE_OR_THREE (2 + 8)
#define ZERO_OR_ONE_OR_THREE (1 + 2 + 8)
#define NONE (0)
#define ONE_OR_TWO (2 + 4)
#define ONLY_ONE 2
/*TODO: consider saparte data structure to other file*/
/*represent word of code*/
struct wordCommand
{
    /*TODO:consider changing the label by creating array of labels and indexes and lines*/
    unsigned int address;
    unsigned int machineCode : 12;
    unsigned int ARE : 3;
};

/*represent command (horah)*/
struct command
{
    char *name;
    unsigned int opcode : 4;
    unsigned int funct : 4;
    /*0000 for no addressing, 0001 for 0 addressing (immediate), 0010 for 1 addressing (direct)*/
    /*0100 for 2 addressing(relative), 1000 for 3 addressing (register direct)*/
    unsigned int possibleInAddressing : 4;
    unsigned int possibleOutAddressing : 4;
};
/*represent label that is parameter of command*/
struct labelParams
{
    char *name;    /*the name of the label*/
    int codeIndex; /*the place it was shown in the code*/
    int direct;    /*is it direct addressing(0 if it relative)*/
    int lineNum;   /*the number of the line it is appeared in*/
};

/*the list of commands*/
static struct command comList[NUMBER_OF_COMMANDS];

/*the commands in the memory*/
static struct wordCommand commandWordList[MEMORY_SIZE];

/*the list of the labels paramter*/
static struct labelParams *labelParamsList;
static int commandWordsCounter = 0;
static int labelParamsCounter = 0;
/* add the whole command to the machinecode*/
void addCommand(char *commandName, char *param1, char *param2, int lineNum, int *error)
{
    /*TODO: what happens when 1 param is recived*/
    int index;
    struct wordCommand thisWord;
    struct wordCommand param1Word;
    struct wordCommand param2Word;
    /*checking which command was recived, if command is not valid print error */
    if ((index = getCommandIndex(commandName)) == -1)
    {
        printf("Error:line %d, command name is not a valid", lineNum);
        (*error) = ERROR;
        return;
    }
    /*add the opcode the address and the ARE of the current command of the command*/
    struct command thisCom = comList[index];
    thisWord.address = commandWordsCounter;
    thisWord.machineCode = 0;
    thisWord.machineCode = (thisCom.opcode << 4) + thisCom.funct;
    thisWord.machineCode <<= 8;
    thisWord.ARE = us_binary_to_int("100")
        /*handling the input parameter*/
        if (thisCom.possibleInAddressing != NULL)
    {
    }
    if (comList[index].possibleOutAddressing != NULL)
    {
        /* code */
    }
}
/*update all the commands that wasent completed in iteration 1*/
void updateCommands(int *error)
{
}
/* get all the words in the output format*/
void getcommandWordsList(char *as, char *ext)
{
}
/*get the number of command words*/
int getcommandWordsCounter()
{
}

void initializeCommands()
{
    /*initialize command list*/
    comList[0].name = "mov";
    comList[0].opcode = 0;
    comList[0].funct = 0;
    comList[0].possibleInAddressing = ZERO_OR_ONE_OR_THREE; /*0,1,3*/
    comList[0].possibleOutAddressing = ONE_OR_THREE;        /*1,3*/
    /**/
    comList[1].name = "cmp";
    comList[1].opcode = 1;
    comList[1].funct = 0;
    comList[1].possibleInAddressing = ZERO_OR_ONE_OR_THREE;  /*0,1,3*/
    comList[1].possibleOutAddressing = ZERO_OR_ONE_OR_THREE; /*0,1,3*/
    /**/
    comList[2].name = "add";
    comList[2].opcode = 2;
    comList[2].funct = 10;
    comList[2].possibleInAddressing = ZERO_OR_ONE_OR_THREE; /*0,1,3*/
    comList[2].possibleOutAddressing = ONE_OR_THREE;        /*1,3*/
    /**/
    comList[3].name = "sub";
    comList[3].opcode = 2;
    comList[3].funct = 11;
    comList[3].possibleInAddressing = ZERO_OR_ONE_OR_THREE; /*0,1,3*/
    comList[3].possibleOutAddressing = ONE_OR_THREE;        /*1,3*/
    /**/
    comList[4].name = "lea";
    comList[4].opcode = 4;
    comList[4].funct = 0;
    comList[4].possibleInAddressing = ONLY_ONE;      /*1*/
    comList[4].possibleOutAddressing = ONE_OR_THREE; /*1,3*/
    /**/
    comList[5].name = "clr";
    comList[5].opcode = 5;
    comList[5].funct = 10;
    comList[5].possibleInAddressing = NONE;          /*none*/
    comList[5].possibleOutAddressing = ONE_OR_THREE; /*1,3*/
    /**/
    comList[6].name = "not";
    comList[6].opcode = 5;
    comList[6].funct = 11;
    comList[6].possibleInAddressing = NONE;          /*none*/
    comList[6].possibleOutAddressing = ONE_OR_THREE; /*1,3*/
    /**/
    comList[7].name = "inc";
    comList[7].opcode = 5;
    comList[7].funct = 12;
    comList[7].possibleInAddressing = NONE;          /*none*/
    comList[7].possibleOutAddressing = ONE_OR_THREE; /*1,3*/
    /**/
    comList[8].name = "dec";
    comList[8].opcode = 5;
    comList[8].funct = 13;
    comList[8].possibleInAddressing = NONE;          /*none*/
    comList[8].possibleOutAddressing = ONE_OR_THREE; /*1,3*/
    /**/
    comList[9].name = "jmp";
    comList[9].opcode = 9;
    comList[9].funct = 10;
    comList[9].possibleInAddressing = NONE;        /*none*/
    comList[9].possibleOutAddressing = ONE_OR_TWO; /*1,2*/
    /**/
    comList[10].name = "bne";
    comList[10].opcode = 9;
    comList[10].funct = 11;
    comList[10].possibleInAddressing = NONE;        /*none*/
    comList[10].possibleOutAddressing = ONE_OR_TWO; /*1,2*/
    /**/
    comList[11].name = "jsr";
    comList[11].opcode = 9;
    comList[11].funct = 12;
    comList[11].possibleInAddressing = NONE;        /*none*/
    comList[11].possibleOutAddressing = ONE_OR_TWO; /*1,2*/
    /**/
    comList[12].name = "red";
    comList[12].opcode = 12;
    comList[12].funct = 0;
    comList[12].possibleInAddressing = NONE;          /*none*/
    comList[12].possibleOutAddressing = ONE_OR_THREE; /*1,3*/
    /**/
    comList[13].name = "prn";
    comList[13].opcode = 13;
    comList[13].funct = 0;
    comList[13].possibleInAddressing = NONE;                  /*none*/
    comList[13].possibleOutAddressing = ZERO_OR_ONE_OR_THREE; /*0,1,3*/
    /**/
    comList[14].name = "rts";
    comList[14].opcode = 14;
    comList[14].funct = 0;
    comList[14].possibleInAddressing = NONE;  /*none*/
    comList[14].possibleOutAddressing = NONE; /*none*/
    /**/
    comList[15].name = "stop";
    comList[15].opcode = 15;
    comList[15].funct = 0;
    comList[15].possibleInAddressing = NONE;  /*none*/
    comList[15].possibleOutAddressing = NONE; /*none*/
}
/*get the index of the command, if command no exits return -1*/
static int getCommandIndex(char *commandName)
{
    int i = 0;
    for (i = 0; i < NUMBER_OF_COMMANDS; i++)
    {
        if (strcmp(comList[i].name, commandName) == 0)
        {
            return i;
        }
    }
    return -1;
}

/*handle the parameter(add the right adressing to the command, print error if accrued) and return the word that represent this parameter*/
static void handleParam(int isFirsstParam, char *param, struct wordCommand commandWord, int possibleInAddressing, int lineNum, int *error)
{

    /*if it could be in immidiate addressing*/
    if (us_binary_to_int("0001") & possibleInAddressing)
    {
        /*if it is immediate addressing*/
        if (checkIfImmidiate(param))
        {
            handleImmediate(param, lineNum, error);
            return;
        }
    }
    /*(skip direct addressing because checking if somthing is tag is less efficient direct adressing will be checked at the end)*/

    /*if it could be relative addressing*/
    if (us_binary_to_int("0100") & possibleInAddressing)
    {
        /*if it is relative addressing*/
        if (checkIfRelative(param))
        {
            unsigned int mask = 2;
            /*if it is in param move it 2 to the left*/
            if (isFirsstParam)
            {
                mask <<= 2;
            }
            commandWord.machineCode |= mask;
            handleRelative(param, lineNum, error);
            return;
        }
    }

    /*if it could be register direct addressing*/
    if (us_binary_to_int("1000") & possibleInAddressing)
    {
        /*if it is register direct addressing*/
        if (checkIfRegisterDirect(param))
        {
            unsigned int mask = 3;
            /*if it is in param move it 2 to the left*/
            if (isFirsstParam)
            {
                mask <<= 2;
            }
            commandWord.machineCode |= mask;
            handleRegisterDirect(param, lineNum, error);
            return;
        }
    }

    /*if it could be direct addressing*/
    if (us_binary_to_int("0010") & possibleInAddressing)
    {
        unsigned int mask = 3;
        /*if it is in param move it 2 to the left*/
        if (isFirsstParam)
        {
            mask <<= 2;
        }
        commandWord.machineCode |= mask;
        handleDirect(param, lineNum, error);
        return;
    }
    printf("Error: line %d, parameter is not valid", lineNum);
    (*error) = ERROR;
}
/*checking if the parameter is in the direct addressing format*/
static int checkIfImmidiate(char *param)
{
    return param[0] == IMMEDIATE_SPECIFIER;
}
/*checking if the parameter is in the relative addressing format*/
static int checkIfRelative(char *param)
{
    return param[0] == RELATIVE_SPECIFIER;
}
/*checking if the parameter is in the register direct addressing format*/
static int checkIfRegisterDirect(char *param)
{
    return strlen(param) == 2 && param[0] == 'r' && (param[1] - '0') >= 0 && param[1] <= MAX_REGISTER;
}
/*checking if the parameter is in the direct addressing format*/
static int checkIfDirect(char *param)
{
    return isValidLabel(param);
}

/*handle immidiate parameter, by adding it to the commandWordList if everything is ok , assuming that it is immidiate parameter*/
static void handleImmidiate(char *param, int lineNum, int *error)
{
    char *numberStr = substring(1, strlen(param), param);
    int number = atoi(numberStr);
    /*check if the number is valid -
    /* if the parmater is zeo ther are two options:
    or it really is is zero or that atoi was returning zero because it is not a number
    if the number is not zero checking that it in the ranges*/
    if ((number == 0 && !checkIfZero(number) || !isValidNumber(number)))
    {
        printf("Error: line %d, number is not valid", lineNum);
        (*error) = ERROR;
        return;
    }
    struct wordCommand result;
    addCommandWord(number, us_binary_to_int("100"));
}
/*handle relative parameter, by adding empty word to the command words list and add the parameter to the label param list if everything is ok.
 assuming that it is direct parameter*/
static void handleRelative(char *param, int lineNum, int *error)
{
    addLabelParam(param, 0,lineNum);
}
/*handle register direct parameter, by adding it to the commandWordList if everything is ok , assuming that it is register direct parameter*/
static void handleRegisterDirect(char *param, int lineNum, int *error)
{
    int number = param[1] - '0';
    unsigned int machineCode = 1;
    machineCode <<= number;
    struct wordCommand result;
    addCommandWord(machineCode, us_binary_to_int("100"));
    return;
}
/*handle direct parameter, by adding empty word to the command words list and add the parameter to the label param list if everything is ok.
 assuming that it is direct parameter*/
static void handleDirect(char *param, int lineNum, int *error)
{
    addLabelParam(param, 1,lineNum);
}
/*add the paramter to the parm label list and add empty word with R for relative to the commandWordList*/
static void addLabelParam(char *name, int direct, int lineNum)
{
    labelParamsList = (struct labelParams *)myRealloc(labelParamsList, (labelParamsCounter + 2) * sizeof(struct labelParams));
    labelParamsList[labelParamsCounter].name = name;
    labelParamsList[labelParamsCounter].codeIndex = commandWordsCounter;
    labelParamsList[labelParamsCounter].direct = direct;
    labelParamsList[labelParamsCounter].lineNum = lineNum;
    addCommandWord(0, us_binary_to_int("010"));
}
/*add command word to the command word list*/
static void addCommandWord(int machineCode, int ARE)
{
    commandWordList[commandWordsCounter].address = FIRST_ADDRESS + commandWordsCounter;
    commandWordList[commandWordsCounter].machineCode = machineCode;
    commandWordList[commandWordsCounter].ARE = ARE;
}
/*TODO: after splitting to files add bound check fall the methods*/