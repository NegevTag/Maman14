#include "header.h"
#define ONE_OR_THREE (2 + 8)
#define ZERO_OR_ONE_OR_THREE (1 + 2 + 8)
#define NONE (0)
#define ONE_OR_TWO (2 + 4)

//represent word of code;
struct codeInstruaction
{
    unsigned int address;
    unsigned int machineCode : 12;
    unsigned int ARE : 3;
    char *label;
};

//represent command (horah)
struct command
{
    char *name;
    unsigned int opcode : 4;
    unsigned int funct : 4;
    //0000 for no addressing, 0001 for 0 addressing (immediate), 0010 for 1 addressing (direct)
    //0100 for 2 addressing(relative), 1000 for 3 addressing (register direct)
    unsigned int possibleInAddressing : 4;
    unsigned int possibleOutAddressing : 4;
};
//the list of commands
static struct command comList[NUMBER_OF_COMMANDS];

void initializecodeInstruction()
{
    //initialize command list
    comList[0].name = "mov";
    comList[0].opcode = 0;
    comList[0].funct = 0;
    comList[0].possibleInAddressing = ZERO_OR_ONE_OR_THREE; //0,1,3
    comList[0].possibleInAddressing = ONE_OR_THREE;         //1,3
    //
    comList[1].name = "cmp";
    comList[1].opcode = 1;
    comList[1].funct = 0;
    comList[1].possibleInAddressing = ZERO_OR_ONE_OR_THREE; //0,1,3
    comList[1].possibleInAddressing = ZERO_OR_ONE_OR_THREE; //0,1,3
    //
    comList[2].name = "add";
    comList[2].opcode = 2;
    comList[2].funct = 10;
    comList[2].possibleInAddressing = ZERO_OR_ONE_OR_THREE; //0,1,3
    comList[2].possibleInAddressing = ONE_OR_THREE;         //1,3
    //
    comList[3].name = "sub";
    comList[3].opcode = 2;
    comList[3].funct = 11;
    comList[3].possibleInAddressing = ZERO_OR_ONE_OR_THREE; //0,1,3
    comList[3].possibleInAddressing = ONE_OR_THREE;         //1,3
    //
    comList[4].name = "lea";
    comList[4].opcode = 4;
    comList[4].funct = 0;
    comList[4].possibleInAddressing = us_binary_to_int("0010"); //1
    comList[4].possibleInAddressing = ONE_OR_THREE;             //1,3
    //
    comList[5].name = "clr";
    comList[5].opcode = 5;
    comList[5].funct = 10;
    comList[5].possibleInAddressing = NONE;         //none
    comList[5].possibleInAddressing = ONE_OR_THREE; //1,3
    //
    comList[6].name = "not";
    comList[6].opcode = 5;
    comList[6].funct = 11;
    comList[6].possibleInAddressing = NONE;         //none
    comList[6].possibleInAddressing = ONE_OR_THREE; //1,3
    //
    comList[7].name = "inc";
    comList[7].opcode = 5;
    comList[7].funct = 12;
    comList[7].possibleInAddressing = NONE;         //none
    comList[7].possibleInAddressing = ONE_OR_THREE; //1,3
    //
    comList[8].name = "dec";
    comList[8].opcode = 5;
    comList[8].funct = 13;
    comList[8].possibleInAddressing = NONE;         //none
    comList[8].possibleInAddressing = ONE_OR_THREE; //1,3
    //
    comList[9].name = "jmp";
    comList[9].opcode = 9;
    comList[9].funct = 10;
    comList[9].possibleInAddressing = NONE;       //none
    comList[9].possibleInAddressing = ONE_OR_TWO; //1,2
    //
    comList[10].name = "bne";
    comList[10].opcode = 9;
    comList[10].funct = 11;
    comList[10].possibleInAddressing = NONE;       //none
    comList[10].possibleInAddressing = ONE_OR_TWO; //1,2
    //
    comList[11].name = "jsr";
    comList[11].opcode = 9;
    comList[11].funct = 12;
    comList[11].possibleInAddressing = NONE;       //none
    comList[11].possibleInAddressing = ONE_OR_TWO; //1,2
    //
    comList[12].name = "red";
    comList[12].opcode = 12;
    comList[12].funct = 0;
    comList[12].possibleInAddressing = NONE;         //none
    comList[12].possibleInAddressing = ONE_OR_THREE; //1,3
    //
    comList[13].name = "prn";
    comList[13].opcode = 13;
    comList[13].funct = 0;
    comList[13].possibleInAddressing = NONE;                 //none
    comList[13].possibleInAddressing = ZERO_OR_ONE_OR_THREE; //0,1,3
    //
    comList[14].name = "rts";
    comList[14].opcode = 14;
    comList[14].funct = 0;
    comList[14].possibleInAddressing = NONE; //none
    comList[14].possibleInAddressing = NONE; //none
    //
    comList[15].name = "stop";
    comList[15].opcode = 15;
    comList[15].funct = 0;
    comList[15].possibleInAddressing = NONE; //none
    comList[15].possibleInAddressing = NONE; //none
}
int main(int argc, char const *argv[])
{
    int i, j;
    for (i = 0; i < NUMBER_OF_COMMANDS; i++)
    {
        switch (comList[i].possibleOutAddressing)
        {
        case ONE_OR_THREE:
            printf("1,3 \t");
            break;

        case ZERO_OR_ONE_OR_THREE:
            printf("0,1,3 \t");
            break;

        case NONE:
            printf("None \t");
            break;
        case ONE_OR_TWO: 
            printf("1,2 \t");
            break;
        case 2:
            printf("1 \t");
            break;
        }

        switch (comList[i].possibleInAddressing)
        {
        case ONE_OR_THREE:
            printf("1,3 \t");
            break;

        case ZERO_OR_ONE_OR_THREE:
            printf("0,1,3 \t");
            break;

        case NONE:
            printf("None \t");
            break;
        case ONE_OR_TWO: 
            printf("1,2 \t");
            break;
        case 2:
            printf("1 \t");
            break;
        }
        printf("* \t",comList[i].name);
        printf("%d \t", comList[i].funct);
        printf("%d \t", comList[i].opcode);
        printf("\n");

    }
