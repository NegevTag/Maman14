#include "header.h"

/*TODO: check if tag is the same*/
/*return if string is tag*/
int isValidTag(char *tag,int withColon)
{
}
/*return if string is defined tag*/
int isDefined(char *tag)
{
}
/* -1 if in data*/
void addTag(char *tag, int withColon, int address, int data, int external, int entry, int lineNumber, int *error)
{
}
void addTempTag(char *tag, int lineNumber, int *error, int withColon)
{
}
void removeTempTag()
{
}
char *getTempTag()
{
}
/*make the temporary tag permanent, reciving the tag adress and wether is data or code and wether is extrnal and wether it is entry
if it is data adress should be the adress of the data */
void *makeTempTagPermanent(int address, int data, int external, int entry)
{
}
void updateTags()
{
    /*update all the tags spots*/
}
char *getInternalList()
{
}