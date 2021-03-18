/*represent the list of labels that should be entry*/
#include "projectHeader.h"
#include "instructionHeader.h"
struct entry
{
    char *label;
    int lineNum;
};

static struct entry(*entryList);
static int entryIndex;
static int isAlreadyInList(char *label);
/*add entry to the entry list, return ERROR if accrued*/
int addEntry(char *label, int lineNum)
{
    if (!isAlreadyInList(label))
    {
    /*allocate new memory for the entryList*/
    entryList = (struct entry *)myRealloc(entryList, (entryIndex + 2) * sizeof(struct entry));
    /*add entry to the list*/
    entryList[entryIndex].lineNum = lineNum;
    /*there is no need to allocate memory for the string because substring allocate memory*/
    entryList[entryIndex].label = label;
    entryIndex++;
    return 1;
    }
    return ERROR;
}
/*initialize the entryList*/
void initializeEntryList()
{
    entryList = (struct entry *)(myMalloc(sizeof(struct entry)));
    entryIndex = 0;
}
/*get the number of entry variables*/
int getNumberOfEntries()
{
    return entryIndex;
}
/*return the label of the entry in the index, return NULL if it is out of range*/
char *getEntryLabel(int index, int *lineNum)
{
    if (index >= 0 && index < entryIndex)
    {
        *lineNum = entryList[index].lineNum;
        return entryList[index].label;
    }
    return NULL;
}
/*return true if the label is already in the list*/
static int isAlreadyInList(char *label){
    int i;
    for (i = 0; i < entryIndex; i++)
    {
        if (strcmp(entryList[i].label, label) == 0)
        {
            return 1;
        }
    }
    return 0;
}