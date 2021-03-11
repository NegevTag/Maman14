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
/* return memory allocated substring of str, between start (include) and finish (exclude)
if there was an error in alloction stop the program*/
char *subString(int start, int end, char *str)
{
    /* allocate memory for the result*/
    char *result = (char *)myMalloc(sizeof(char) * (end - start));
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
int min(int x, int y)
{
    return x < y ? x : y;
}
/*allocate memory and exit if problem accrued*/
void *myMalloc(int size)
{
    void *result = malloc(size);
    if (!result)
    {
        printf("Error: memory allocation failed");
        exit(0);
    }
    return result;
}

/*reallocate memory and exit if problem accrued  */
void *myRealloc(int *ptr, int size)
{
    void *temp = realloc(ptr, size);
    if (!temp)
    {
        printf("Error: memory allocation failed");
        exit(0);
    }
    return temp;
}
/*check it the number can be represent is 12 bit*/
int isValidNumber(int number)
{
    return number <= MAX_NUMBER && number >= MIN_NUMBER;
}
/*check if string represent the number zero */
static int checkIfZero(char *zeroStr)
{
    int i = 0;
    int zero = 1;
    int length = strlen(zeroStr);
    if (length == 0)
    {
        return 0;
    }

    zero &= zeroStr[0] == '-' || zeroStr[0] == '+' || zeroStr[0] == '0';
    for (i = 0; i < length; i++)
    {
        zero &= zeroStr[i] == '0';
    }
    return zero;
}