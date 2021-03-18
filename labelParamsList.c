/*represent the list of the paramter for commands that are labels*/
/*not responsible for printing error message if occures*/
#include "projectHeader.h"
#include "commandsHeader.h"

/*the list of the labels paramter*/
static struct labelParam *labelParamsList;

static int lastIndex = 0;

static int firstIndex = 0;
/*add the paramter to the parm label list and add empty commandWord that will represent the paramterafter iteration2, return ERROR if error occurred**/
int addLabelParam(char *name, int direct, int lineNum)
{
    labelParamsList = (struct labelParam *)myRealloc(labelParamsList, (lastIndex + 2) * sizeof(struct labelParam));
    labelParamsList[lastIndex].name = name;
    labelParamsList[lastIndex].codeParamAddress = getNextCWAddress();
    labelParamsList[lastIndex].direct = direct;
    labelParamsList[lastIndex].lineNum = lineNum;
    lastIndex++;
    if (direct)
    {
        return addCW(0, us_binary_to_int("010"));
    }else{
        return addCW(0, us_binary_to_int("100"));
    }
    
    
}
/*initialize the entryList*/
void initializeLabelParamsList()
{
    labelParamsList = (struct labelParam *)(myMalloc(sizeof(struct labelParam)));
}
/*get the next label parameter, if reached end *reachedEnd will be 1 and trash value will be return*/
struct labelParam getNextLabelParam(int *reachedEnd)
{
    struct labelParam trash;
    if (firstIndex >= 0 && firstIndex < lastIndex)
    {
        (*reachedEnd) = 0;
        return labelParamsList[firstIndex++];
    }
    (*reachedEnd) = 1;
    return trash;
}