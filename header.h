#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FIRST_ADDRESS 100
#define NUMBER_OF_COMMANDS 16
#define MEMORY_SIZE 4096
#define MAX_LINE_LENGTH 80
#define ERROR 1
#define COMMENT_SPECIFIER ';'
#define TAG_SPECIFIER ':'
#define INSTRUCTION_SPECIFIER '.'
/*transferring unsigned binary number shown as string to int*/
int us_binary_to_int(char * binary);