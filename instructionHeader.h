void addWord(int machineCode, int ARE);
int addIWRepresentativeStringToFile(FILE *f, int index);
void addEntry(char *label, int lineNum);
void initializeEntryList();
int getNumberOfEntries();
char *getEntryLabel(int index, int *lineNum);