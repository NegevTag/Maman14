/*represent the list of labels that should be entry*/

static struct entry
{
    char *label;
    int lineNum;
};

/*TODO: make all files more readable (statics done, struct up, functions up)*/
static struct entry(*entryList);
static int entryIndex = 0;
/*add entry to the entry list*/
void addEntry(char *label,int lineNumber)
{
    /*allocate new memory for the entryList*/
    entryList = (struct entry *)myRealloc(entryList, (entryIndex + 2) * sizeof(struct entry));
    /*add entry to the list*/
    entryList[entryIndex].lineNum = lineNumber;
    /*there is no need to allocate memory for the string because substring allocate memory*/
    entryList[entryIndex].label = label;
    entryIndex++;
}
/*initialize the entryList*/
void initializeEntryList()
{
    entryList = (struct entry *)(myMalloc(sizeof(struct entry)));
}
