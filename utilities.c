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