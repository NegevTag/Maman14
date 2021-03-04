#include "header.h"

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
if there was an error it will print the error message and return null */
char *subString(int start, int end, char *str)
{
    /* allocate memory for the result*/
    char *result = (char *)malloc(sizeof(char) * (end - start));
    if (!result)
    {
        printf("Error: memory allocation failed");
        return NULL;
    }

    while (start < end)
    {
        result[start] = str[start];
        start++;
    }
    result[end] = '\0';
    return result;
}