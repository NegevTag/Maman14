#include "projectHeader.h"
/*handling all the labels opartions, not separate from the data structure because it is almost the same as the data structure interface*/

struct label
{
    char *label; /*the label itself, without colon*/
    int address;
    unsigned int data : 1;     /*1 if it is data, 0 if it is code*/
    unsigned int external : 1; /*1 if external, 0 otherwise*/
    unsigned int entry : 1;    /*1 if entry, 0 otherwise*/
    unsigned int lineNum;
};
struct label *labelList;
int labelsCounter;
int tempLabelExists;
char *tempLabelLabel;
int tempLabellineNum;
int tempLabelWithColon;
/*initialize the entryList*/
void initializelabelList()
{
    labelsCounter = 0;
    tempLabelExists = 0;
    labelList = (struct label *)myMalloc(sizeof(struct label));
}

/*return true if string is a valid label*/
int isValidLabel(char *label, int withColon, int okIfAlreadyDefined)
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
    if (strcmp(pureLabel, "data") == 0 || strcmp(pureLabel, "string") == 0 || strcmp(pureLabel, "entry") == 0 || strcmp(pureLabel, "extern") == 0)
    {
        return 0;
    }
    /*checking if the label is register*/
    if(strlen(label) == 2 && label[0] == 'r' && (label[1] - '0') >= 0 && (label[1] - '0') <= MAX_REGISTER){
        return 0;
    }
    /*check that the first char is letter*/
    if (!((pureLabel[0] <= 'z' && pureLabel[0] >= 'a') || (pureLabel[0] <= 'Z' && pureLabel[0] >= 'A')))
    {
        return 0;
    }
    /*if it is ok i*s already defind return true else check if it is already defind*/
    if (okIfAlreadyDefined)
    {
        return 1;
    }
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
/*add label to the label list, if it is not valid change error to ERROR, isParm - is the label parameter at this line (for error output)*/
void addLabel(char *label, int withColon, int address, int data, int external, int entry, int isParam, int lineNum, int *error)
{
    if (!isValidLabel(label, withColon, 0))
    {
        if (isParam)
        {
            printf("Error:line %d, label param is not valid\n", lineNum);
        }else
        {
            printf("Error:line %d, label is not valid\n", lineNum);
        }
        (*error) = ERROR;
        return;
    }
    else
    {
        char *pureLabel = label;
        if (withColon)
        {
            pureLabel = subString(0, strlen(label) - 1, label);
        }
        labelList = (struct label *)myRealloc(labelList, (labelsCounter + 2) * sizeof(struct label));
        labelList[labelsCounter].label = pureLabel;
        labelList[labelsCounter].address = address;
        labelList[labelsCounter].data = data;
        labelList[labelsCounter].external = external;
        labelList[labelsCounter].entry = entry;
        labelList[labelsCounter].lineNum = lineNum;
        labelsCounter++;
    }
}
/*add temporary label assuming it is not parameter , will be overwritten by the next call*/
void addTempLabel(char *label, int lineNum, int *error, int withColon)
{
    if (!isValidLabel(label, withColon, 0))
    {
        printf("Error:line %d, label is not valid\n", lineNum);
        (*error) = ERROR;
        return;
    }
    tempLabelExists = 1;
    tempLabelLabel = label;
    tempLabellineNum = lineNum;
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
    /*garbage1 and garbage2 represent the lineNum and the error,
    since addTempLabel already checked if the label is valid addLabel will not use does variables */
    int garbage1 = 0;
    int garbage2 = 0;
    if (tempLabelExists)
    {
        addLabel(tempLabelLabel, tempLabelWithColon, address, data, external, entry,0, garbage1, &garbage2);
        tempLabelExists = 0;
    }
}

/*updating the address of the data labels*/
void updateLabels()
{
    int i;
    /*update all the data labels adress*/
    for (i = 0; i < labelsCounter; i++)
    {
        if (labelList[i].data == 1)
        {
            /*if the label is external it shouldnt be updated*/
            if (labelList[i].external == 0)
            {
                labelList[i].address += getNextCWAddress();
            }
        }
    }
}
/*set label to entry, if label not exist or label is entry print the error and change error to ERROR, return the address of the label and ERROR if occurred */
int setEntry(char *label, int lineNum, int *error)
{
    int i;
    for (i = 0; i < labelsCounter; i++)
    {
        if (strcmp(labelList[i].label, label) == 0)
        {
            /*internal lablel cant be external*/
            if (labelList[i].external == 1)
            {
                printf("Error, line %d, label cannot be external and entry\n", lineNum);
                (*error) = ERROR;
                return ERROR;
            }
            else
            {
                labelList[i].entry = 1;
                return labelList[i].address;
            }
        }
    }
    printf("Error: line %d, entry label parameter wasent declared\n", lineNum);
    (*error) = ERROR;
    return ERROR;
}
/*get address of specified label and change external to wether this label is extranl*/
/*, if error occurred print it and change  *error to ERROR */
int getLabelAddress(char *label, int *external, int lineNum, int *error)
{
    int i;
    for (i = 0; i < labelsCounter; i++)
    {
        if (strcmp(labelList[i].label, label) == 0)
        {
            (*external) = labelList[i].external;
            return labelList[i].address;
        }
    }
    printf("Error: line %d, label parameter wasent declared\n", lineNum);
    (*error) = ERROR;
    return ERROR;
}
