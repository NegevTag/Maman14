#include "header.h"

/*TODO: check if tag is the same*/
/*return if string is tag*/
int isValidTag(char *tag)
{
}
/*return if string is defined tag*/
int isDefined(char *tag)
{
}
/* -1 if in data*/
void addTag(char *tag,int address, int attribute)
{
}
void addTempTag(char *tag){

}
void removeTempTag(){

}
char * getTempTag(){

}
/*make the temporary tag permanent, reciving the tag adress and wether is data or code and wether is extrnal and wether it is entry
if it is data adress should be the adress of the data */
void * makeTempTagPermanent(int address, int data, int external, int entry){

}
void updateTags()
{
    /*update all the tags spots*/
}  
char *getInternalList()
{
}