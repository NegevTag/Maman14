#include "header.h"
/*handling all the labels opartions, not separate from the data structure because it is almost the same as the data structure interface*/

static struct label
{
    char *label; /*the label itself, without colon*/
    int address;
    unsigned int data : 1;     /*1 if it is data, 0 if it is code*/
    unsigned int external : 1; /*1 if external, 0 otherwise*/
    unsigned int entry : 1;    /*1 if entry, 0 otherwise*/
    unsigned int lineNumber;
};
struct label *labelList;
int labelsCounter = 0;
int tempLabelExists = 0;
char * tempLabelLabel;
int tempLabelLineNumber;
int tempLabelWithColon;
/*initialize the entryList*/
void initializelabelList()
{
    labelList = (struct label *)myMalloc(sizeof(struct label));
}

/*return true if string is a valid label*/
int isValidLabel(char *label, int withColon)
{
    char *pureLabel = label;
    /* empty label is not valid*/
    if (strlen(label) == 0 || (withColon && strlen(label) == 1))
    {
        return 0;
    }
    /*if it specified that the label is with colon check that it indead with colon and remove the colon*/
    if (withColon)
    {
        if (label[strlen(label) - 1] != LABEL_SPECIFIER)
        {
            return 0;
        }
        pureLabel = subString(0, strlen(label) - 1, label);
    }
    /*if the label is the same as some command it not valid */
    if (isCommandExist(pureLabel))
    {
        return 0;
    }
    /*checking if the label is instruction */
    if (strcmp(pureLabel, "data") == 0 || strcmp(pureLabel, "string") == 0 || strcmp(pureLabel, "entry") == 0 || strcmp(pureLabel, "extern" == 0))
    {
        return 0;
    }
    /*return true if everything above was ok and the first char is letter*/
    if (!(label[0] <= 'z' && label[0] >= 'a') || (label[0] <= 'Z' && label[0] >= 'A'))
    {
        return 0;
    }
    /*return 1 if the label isnt already defined*/
    return !isDefinedLabel(pureLabel);
}
/*return if string is defined label*/
int isDefinedLabel(char *purelabel)
{
    int i = 0;
    for (i = 0; i < labelsCounter; i++)
    {
        if (strcmp(labelList[i].label, purelabel) == 0)
        {
            return 1;
        }
    }
    return 0;
}
/*add label to the label list, if it is not valid change error to ERROR*/
void addLabel(char *label, int withColon, int address, int data, int external, int entry, int lineNumber, int *error)
{
    if (!isValidLabel(label, withColon))
    {
        printf("Error:line %d, label is not valid", lineNumber);
        (*error) = ERROR;
        return;
    }
    else
    {
        char * pureLabel = subString(label,strlen(label) -1, label);
        labelList = (struct labelParams *)myRealloc(labelList, (labelsCounter + 2) * sizeof(struct label));
        labelList[labelsCounter].label = label;
        labelList[labelsCounter].address = address;
        labelList[labelsCounter].data = data;
        labelList[labelsCounter].external = external;
        labelList[labelsCounter].entry = entry;
        labelList[labelsCounter].lineNumber = lineNumber;
        labelsCounter++;
    }
}
/*add temporary label, will be overwritten by the next call*/
void addTempLabel(char *label, int lineNumber, int *error, int withColon)
{
    if (!isValidLabel(label, withColon))
    {
        (*error) =ERROR;
        return;
    }
    tempLabelExists = 1;
    tempLabelLabel = label;
    tempLabelLineNumber = lineNumber;
    tempLabelWithColon = withColon;
    
}
/*remove temporary label*/
void removeTempLabel()
{
    tempLabelExists = 0;
}

/*if temporary label exist make the temporary label permanent, otherwise does nothing */
void makeTempLabelPermanent(int address, int data, int external, int entry)
{
    /*garbage1 and garbage2 represent the lineNumber and the error,
    since addTempLabel already checked if the label is valid addLabel will not use does variables */
    int garbage1;
    int garbage2;
    if (tempLabelExists)
    {
        addLabel(tempLabelLabel, tempLabelWithColon, address, data, external, entry, garbage1, &garbage2);
        tempLabelExists = 0;
    }
    
}

void updateLabels()
{
    /*update all the labels spots*/
}
char *getInternalList()
{
}
