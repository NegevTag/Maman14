/* handling all commands (horaa) operations for iteration 1 and 2 */
#include "header.h"
#include "commandsHeader.h"

/* add the whole command to the machinecode, if only 1 paramter recived param2 should be null*/
void addCommand(char *commandName, char *param1, char *param2, int lineNum, int *error)
{
    /*TODO: what happens when 1 param is recived*/
    int index;
    unsigned int machineCode =0;
    int currentError = 0;
    /*the command that this word represent*/
    struct command thisCom;
    /*checking which command was recived, if command is not valid print error */
    if ((index = getCommandIndex(commandName)) == -1)
    {
        printf("Error:line %d, command name is not a valid", lineNum);
        (*error) = ERROR;
        return;
    }
    thisCom = comList[index];
    /*add the opcode the address and the ARE of the current command of the command*/
    machineCode = 0;
    machineCode = (thisCom.opcode << 4) + thisCom.funct;
    machineCode <<= 8;
    addCommandWord(machineCode,us_binary_to_int("100"));
    /**add words that represent the parmater*/
    if (param2!=NULL)
    {
        handleParam(1,param1,thisCom.opcode,lineNum,*currentError);
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




/*handle the parameter(add the appropriate word to the command word list, print error if accrued) 
commandWord is the word that represent the command which this is the parameter for it */
static void handleParam(int isInputParam, char *param, struct wordCommand commandWord, int possibleAddressing, int lineNum, int *error)
{
    /*if it could be in immidiate addressing*/
    if (us_binary_to_int("0001") & possibleAddressing)
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
    if (us_binary_to_int("0100") & possibleAddressing)
    {
        /*if it is relative addressing*/
        if (checkIfRelative(param))
        {
            unsigned int mask = 2;
            /*if it is in param move it 2 to the left*/
            if (isInputParam)
            {
                mask <<= 2;
            }
            commandWord.machineCode |= mask;
            handleRelative(param, lineNum, error);
            return;
        }
    }

    /*if it could be register direct addressing*/
    if (us_binary_to_int("1000") & possibleAddressing)
    {
        /*if it is register direct addressing*/
        if (checkIfRegisterDirect(param))
        {
            unsigned int mask = 3;
            /*if it is in param move it 2 to the left*/
            if (isInputParam)
            {
                mask <<= 2;
            }
            commandWord.machineCode |= mask;
            handleRegisterDirect(param, lineNum, error);
            return;
        }
    }

    /*if it could be direct addressing*/
    if (us_binary_to_int("0010") & possibleAddressing)
    {
        unsigned int mask = 3;
        /*if it is in param move it 2 to the left*/
        if (isInputParam)
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
    addCommandWord(machineCode, us_binary_to_int("100"));
    return;
}
/*handle direct parameter, by adding empty word to the command words list and add the parameter to the label param list if everything is ok.
 assuming that it is direct parameter*/
static void handleDirect(char *param, int lineNum, int *error)
{
    addLabelParam(param, 1,lineNum);
}


/*TODO: after splitting to files add bound check fall the methods*/