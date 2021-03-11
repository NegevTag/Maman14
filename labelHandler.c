#include "header.h"


/*return if string is label*/
int isValidLabel(char *label,int withColon)
{
    /*check if label is the same as other*/
}
/*return if string is defined label*/
int isDefined(char *label)
{
}
void addLabel(char *label, int withColon, int address, int data, int external, int entry, int lineNumber, int *error)
{
}
void addTempLabel(char *label, int lineNumber, int *error, int withColon)
{
}
void removeTempLabel()
{
}
char *getTempLabel()
{
}
/*make the temporary label permanent, reciving the label adress and wether is data or code and wether is extrnal and wether it is entry
if it is data adress should be the adress of the data */
void *makeTempLabelPermanent(int address, int data, int external, int entry)
{
}
void updateLabels()
{
    /*update all the labels spots*/
}
char *getInternalList()
{
}