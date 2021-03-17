/* handling all commands (horaa) operations for iteration 1 and 2 */
#include "projectHeader.h"
#include "commandsHeader.h"

static void handleParam(int isInputParam, char *param, int commandWordAddress, int possibleAddressing, int lineNum, int *error);
static int checkIfImmidiate(char *param);
static int checkIfRelative(char *param);
static int checkIfRegisterDirect(char *param);
static int checkIfDirect(char *param);
static void handleImmidiate(char *param, int lineNum, int *error);
static void handleRelative(char *param, int lineNum, int *error);
static void handleRegisterDirect(char *param, int lineNum, int *error);
static void handleDirect(char *param, int lineNum, int *error);
/* add the whole command to the machinecode, if only 1 paramter recived param2 should be null*/
void addCommand(char *commandName, char *param1, char *param2, int lineNum, int *error)
{
    unsigned int machineCode = 0;
    int currentError = 0;
    int commandAdress;
    /*the command that this word represent*/
    struct command thisCom;
    /*checking which command was recived, if command is not valid print error */
    thisCom = getCommand(commandName, &currentError);
    if (currentError == ERROR)
    {
        printf("Error:line %d, command name is not a valid\n", lineNum);
        (*error) = ERROR;
        return;
    }
    /*add the opcode the address and the ARE of the current command of the command*/
    machineCode = 0;
    machineCode = (thisCom.opcode << 4) + thisCom.funct;;
    machineCode <<= 4;
    commandAdress = getNextCWAddress();
    addCW(machineCode, us_binary_to_int("100"));
    /**add words that represent the parmater*/
    /*if there are 2 params the first is the input and the second is the output*/
    if (param2 != NULL)
    {
        handleParam(1, param1, commandAdress, thisCom.possibleInAddressing, lineNum, &currentError);
        if (currentError == ERROR)
        {
            (*error) = ERROR;
            return;
        }
        handleParam(0, param2, commandAdress, thisCom.possibleInAddressing, lineNum, &currentError);
    }
    /*if there is only one parameter it is output parameter*/
    else
    {
        handleParam(0, param1, commandAdress, thisCom.possibleOutAddressing, lineNum, &currentError);
    }
}
/*update all the commands that wasent completed in iteration 1, and filling .ext file and .ob file*/
void updateCommands(char *fileName, int *error)
{
    int i;
    int reachedEnd = 0;
    int external = 0;
    int extEmpty = 1;
    struct labelParam nextLabelParam;
    FILE *ext = fopen(strcat(fileName, ".ext"), "w");
    FILE *ob = fopen(strcat(fileName, ".ob"), "w");
    if (!ob || !ext)
    {
        printf("Error: could not open file\n");
        (*error) = ERROR;
        return;
    }
    nextLabelParam = getNextLabelParam(&reachedEnd);
    /*for each command word update if it is include label parameter and print the output to the file*/
    for (i = 0; i < getNumberOfCW(); i++)
    {
        /*if line with label param reached update the command word to the label adress *
        and if it is extrnal add it to the extrnal list and change to E in ARE*/
        if (!reachedEnd && nextLabelParam.codeAddress == i + FIRST_ADDRESS)
        {
            int labelAdress;
            labelAdress = getLabelAddress(nextLabelParam.name, &external, nextLabelParam.lineNum, error);

            /* if the variable is external add it to the ext file and change to E*/
            if (external)
            {
                changeCWToExternal(nextLabelParam.codeAddress);
                extEmpty = 0;
                if (*error != ERROR)
                {
                    fprintf(ext, "%s %d", nextLabelParam.name, nextLabelParam.codeAddress);
                }
            }
            /*set the machine code of the word that represent the parameter to the parameter address */
            setCWMachineCode(labelAdress, nextLabelParam.codeAddress);
            nextLabelParam = getNextLabelParam(&reachedEnd);
        }
        if (*error != ERROR)
        {
            addCWRepresentativeStringToFile(ob, i + FIRST_ADDRESS);
        }
    }
    fclose(ob);
    fclose(ext);
    /*if error occurred deletd file*/
    if ((*error = ERROR))
    {
        remove(strcat(fileName, ".en"));
        remove(strcat(fileName, ".ob"));
    }
    else if (extEmpty)
    {
        remove(strcat(fileName, ".en"));
    }
}

/*handle the parameter(add the appropriate word to the command word list, print error if accrued) 
commandWordAddress is the address of theword that represent the command which this is the parameter for it */
static void handleParam(int isInputParam, char *param, int commandWordAddress, int possibleAddressing, int lineNum, int *error)
{
    int machineCode = getCWMachineCode(commandWordAddress);
    /*if it could be in immidiate addressing*/
    if (us_binary_to_int("0001") & possibleAddressing)
    {
        /*if it is immediate addressing*/
        if (checkIfImmidiate(param))
        {
            handleImmidiate(param, lineNum, error);
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
            setCWMachineCode(commandWordAddress, machineCode | mask);
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
            setCWMachineCode(commandWordAddress, machineCode | mask);
            handleRegisterDirect(param, lineNum, error);
            return;
        }
    }

    /*if it could be direct addressing*/
    if (us_binary_to_int("0010") & possibleAddressing)
    {
        if (checkIfDirect(param))
        {

            unsigned int mask = 3;
            /*if it is in param move it 2 to the left*/
            if (isInputParam)
            {
                mask <<= 2;
            }
            setCWMachineCode(commandWordAddress, machineCode | mask);
            handleDirect(param, lineNum, error);
            return;
        }
    }
    printf("Error: line %d, parameter is not valid\n", lineNum);
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
    return isValidLabel(param, 0,1);
}

/*handle immidiate parameter, by adding it to the commandWordList if everything is ok , assuming that it is immidiate parameter*/
static void handleImmidiate(char *param, int lineNum, int *error)
{
    char *numberStr = subString(1, strlen(param), param);
    int number = atoi(numberStr);
    /*check if the number is valid -
    if the parmater is zeo ther are two options:
    or it really is is zero or that atoi was returning zero because it is not a number
    if the number is not zero checking that it in the ranges*/
    if ((number == 0 && !checkIfZero(numberStr)) || !isValidNumber(number))
    {
        printf("Error: line %d, number is not valid\n", lineNum);
        (*error) = ERROR;
        return;
    }
    addCW(number, us_binary_to_int("100"));
}
/*handle relative parameter, by adding empty word to the command words list and add the parameter to the label param list if everything is ok.
 assuming that it is direct parameter*/
static void handleRelative(char *param, int lineNum, int *error)
{
    addLabelParam(param, 0, lineNum);
}
/*handle register direct parameter, by adding it to the commandWordList if everything is ok , assuming that it is register direct parameter*/
static void handleRegisterDirect(char *param, int lineNum, int *error)
{
    int number = param[1] - '0';
    unsigned int machineCode = 1;
    machineCode <<= number;
    addCW(machineCode, us_binary_to_int("100"));
}
/*handle direct parameter, by adding empty word to the command words list and add the parameter to the label param list if everything is ok.
 assuming that it is direct parameter*/
static void handleDirect(char *param, int lineNum, int *error)
{
    addLabelParam(param, 1, lineNum);
}
