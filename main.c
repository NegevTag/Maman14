#include "header.h"
int main(int argc, char const *argv[])
{
    int i;
    if (argc == 1)
    {
        printf("Error: At least one file must be specified.\n");
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            FILE *f = fopen(argv[i], "r");
            if (!f)
            {
                printf("Error: could not open file %s.as \n", argv[i]);
            }
            else
            {
               process(f);
            }
            fclose(f);
        }
    }
}
