#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FIRST_ADDRESS 100
#define NUMBER_OF_COMMANDS 16
#define MEMORY_SIZE 4096
#define MAX_LINE_LENGTH 80
/*if there was an error this number indicate it, should always be different from 0*/
#define ERROR -1
#define COMMENT_SPECIFIER ';'
#define LABEL_SPECIFIER ':'
#define INSTRUCTION_SPECIFIER '.'
#define STRING_SPECIFIER "\""
#define IMMEDIATE_SPECIFIER '#'
#define RELATIVE_SPECIFIER '%'
/*2^11 - 1*/
#define MAX_NUMBER 2047
/*-2^11*/
#define MIN_NUMBER 2048
#define MAX_REGISTER 7
/*transferring unsigned binary number shown as string to int*/
int us_binary_to_int(char *binary);
char *subString(int start, int end, char *str);
int min(int x, int y);
void *myMalloc(int size);
void *myRealloc(int *ptr, int size);
int isValidNumber(int number);
int checkIfZero(char *zeroStr);
void initializelabelList();
int isValidLabel(char *label, int withColon);
int isDefinedLabel(char *purelabel);
void addLabel(char *label, int withColon, int address, int data, int external, int entry, int lineNum, int *error);
void addTempLabel(char *label, int lineNum, int *error, int withColon);
void removeTempLabel();
void makeTempLabelPermanent(int address, int data, int external, int entry);
void updateLabels();
int setEntry(char *label, int lineNum, int *error);
int getLabelAddress(char *label, int *external, int lineNum, int *error);
char *getinstructionsWordsList();
void updateEntryInstructions(char *fileName, int *error);
void appendInstructionToOutput(char *fileName, int *error);
void addEInstruction(char *instruction, char *param, int lineNum, int *error);
void addDataInstruction(char *instruction, int params[], int numberOfParams, int lineNum, int *error);
void addStringInstruction(char *instruction, char *param, int lineNum, int *error);
void addCommand(char *commandName, char *param1, char *param2, int lineNum, int *error);
void updateCommands(int *error, char *fileName);
