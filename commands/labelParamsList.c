/*represent the list of the paramter for commands that are labels*/
/*not responsible for printing error message if occures*/

static struct labelParams
{
    char *name;    /*the name of the label*/
    int codeAddress; /*the place it was shown in the code*/
    int direct;    /*is it direct addressing(0 if it relative)*/
    int lineNum;   /*the number of the line it is appeared in*/
};
/*the list of the labels paramter*/
static struct labelParams *labelParamsList;

static int labelParamsCounter = 0;
/*add the paramter to the parm label list and add empty commandWord that will represent the paramterafter iteration2, return ERROR if error occurred**/
int addLabelToList(char *name, int direct, int lineNum)
{
    labelParamsList = (struct labelParams *)myRealloc(labelParamsList, (labelParamsCounter + 2) * sizeof(struct labelParams));
    labelParamsList[labelParamsCounter].name = name;
    labelParamsList[labelParamsCounter].codeAddress = getNextCWAddress();
    labelParamsList[labelParamsCounter].direct = direct;
    labelParamsList[labelParamsCounter].lineNum = lineNum;
    labelParamsCounter++;
    return addCW(0, us_binary_to_int("010"));
}
/*initialize the entryList*/
void initializeLabelParamsList()
{
    labelParamsList = (struct labelParams *)(myMalloc(sizeof(struct labelParams)));
}

