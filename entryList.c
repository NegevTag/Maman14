/*represent the list of labels that should be entry*/
#include "projectHeader.h"
#include "instructionHeader.h"
struct entry
{
    char *label;
    int lineNum;
};

static struct entry(*entryList);
static int entryIndex = 0;
/*add entry to the entry list*/
void addEntry(char *label, int lineNum)
{
    /*allocate new memory for the entryList*/
    entryList = (struct entry *)myRealloc(entryList, (entryIndex + 2) * sizeof(struct entry));
    /*add entry to the list*/
    entryList[entryIndex].lineNum = lineNum;
    /*there is no need to allocate memory for the string because substring allocate memory*/
    entryList[entryIndex].label = label;
    entryIndex++;
}
/*initialize the entryList*/
void initializeEntryList()
{
    entryList = (struct entry *)(myMalloc(sizeof(struct entry)));
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
