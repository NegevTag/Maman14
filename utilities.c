#include "header.h"
/*utilities functions for the use of others*/
/*transferring unsigned binary number shown as string to int, assuming that the number is legal*/
int us_binary_to_int(char *binary)
{
    int currentFac = 1;
    int size = strlen(binary);
    char *current = binary + size - 1;
    int result = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        result += ((*current) - '0') * currentFac;
        current--;
        currentFac *= 2;
    }
    return result;
}
/* return substring of str, between start (include) and finish (exclude)
if there was an error in alloction stop the program*/
char *subString(int start, int end, char *str)
{
    /* allocate memory for the result*/
    char *result = myStringMalloc(sizeof(char) * (end - start));
    if (!result)
    {
        printf("Error: memory allocation failed");
        exit(1);
    }

    while (start < end)
    {
        result[start] = str[start];
        start++;
    }
    result[end] = '\0';
    return result;
}
int min(int x,int y){
    return x < y ? x : y;
}
/*allocate memory and exit if problem accrued*/
char* myStringMalloc(int size){
    char* result = (char*)malloc(size);
    if (!result)
    {
        printf("Error: memory allocation failed");
        exit(1);
    }
}