/*the list of the diffrent commands (mov,cmp,add, etc) and basic information about them*/
#include "header.h"
#include "commandsHeader.h"
#define ONE_OR_THREE (2 + 8)
#define ZERO_OR_ONE_OR_THREE (1 + 2 + 8)
#define NONE (0)
#define ONE_OR_TWO (2 + 4)
#define ONLY_ONE 2
/*the list of commands*/
static struct command comList[NUMBER_OF_COMMANDS];
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
/*get the command by it name, if command no exits change error to ERROR and return some random command*/
struct command getCommandIndex(char *commandName, int *error)
{
    int i = 0;
    for (i = 0; i < NUMBER_OF_COMMANDS; i++)
    {
        if (strcmp(comList[i].name, commandName) == 0)
        {
            return comList[i];
        }
    }
    (*error) = ERROR;
    return comList[0];
}