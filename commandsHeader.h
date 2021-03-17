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
struct labelParam
{
    char *name;      /*the name of the label*/
    int codeParamAddress; /*the word in the code in which it was the permaterFor*/
    int direct;      /*is it direct addressing(0 if it relative)*/
    int lineNum;     /*the number of the line it is appeared in*/
};
int addCW(int machineCode, int ARE);
int setCWMachineCode(int address, int machineCode);
int getCWMachineCode(int address);
int changeCWToExternal(int address);
int addCWRepresentativeStringToFile(FILE *f, int address);
struct command getCommand(char *commandName, int *exist);
int addLabelParam(char *name, int direct, int lineNum);
struct labelParam getNextLabelParam(int *reachedEnd);

