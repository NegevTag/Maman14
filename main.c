#include "projectHeader.h"
/*הסבר על הפרויקט*/
/* ניסתי לממש את הדברים בצורה קרובה לאלגוריתם עם שני המעברים אבל בדרך שיותר מתאימה לי.
אני חושב שעבודה עם שורות של מילים היא מקור פעמים רבות לבעיות ומאוד לא נוחה.
לכן השתדלתי להכניס את כל מה שאני צריך לעשות עם שורות של קוד לקובץ אחד "אסמבלר" ולתת לקבצי "הנדלר"  לעשות את כל מה שלא קשור לשורות של קוד
ע"י  העברה כפרמטרים להנדלר רק את המידע הרלוונטי בצורה נוחה
 בנוסף על מנת להימנע ממעבר שני על הטקסט קבצי ההנדלר שומרים את המידע הרלוונטי למעבר השני במעבר הראשון ומעדכנים את החסר לאחר מכן 
 הערה: כאשר כתוב שורות של קוד הכוונה היא לא לעבודה עם סטרינגים באופן כללי, אלא לעבודה עם יותר ממילה אחת כסטרינג */

/*open all files and let assembler handle them*/
int main(int argc, char *argv[])
{
    int i;
    FILE *f;
    char  asFileName[MAX_FILE_NAME_LENGTH + 3];
    initializeCommands();
    if (argc == 1)
    {
        printf("Error: At least one file must be specified.\n");
    }
    else
    {
        for (i = 1; i < argc; i++)
        {
            initializeLabelParamsList();
            initializeEntryList();
            initializelabelList();
            initializeCWList();
            initializeIWList();
            strcpy(asFileName, argv[i]);
            strcat(asFileName,".as");
            f = fopen(asFileName, "rt");
            if (!f)
            {
                printf("Error: could not open file %s.as \n", argv[i]);
            }
            else
            {
                printf("\nprocess file %s \n",asFileName);
                process(f, argv[i]);
                fclose(f);
            }
            
        }
    }
    return 0;
}
