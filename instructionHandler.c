/*handling all the instructions (hanchiot)*/
#include "header.h"

/* get all the words in the output format*/
char *getinstructionsWordsList()
{
}
/* update all the addresses of the instructions for iteration2*/
void updateInstructions()
{
    /* update adresses*/
    /*update internal*/

}
int getInstructionsWordsCount(){

}
/*adding e instruction (entry or external) the instruction*/
void addEInstruction(char * instruction,char * params, int lineNumber, int *error){
    /* if instruction is data or string add params to code*/
    /*if instruction is extrnal read params[0] and add it to the tags*/
    /*if instruction is is internal read params[0] and add it to the internal list*/
}
/* add the data instruction (and checking that it is data)*/
void addDataInstruction(char * instruction,int params[], int lineNumber, int *error){
    
}
/* add the string instruction (and checking that it is string)*/
void addStringInstruction(char * instruction,char * params, int lineNumber, int *error){
    
}

