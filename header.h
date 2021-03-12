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
int us_binary_to_int(char * binary);