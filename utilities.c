#include "header.h"

//transferring unsigned binary number shown as string to int
int us_binary_to_int(char * binary){
    int currentFac = 1;
    int size = strlen(binary);
    char * current = binary + size -1;
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        result+= (*current)*currentFac;
        current++;
        currentFac*=2;
    }
    return result;
    
}