#include "bibliographie.h"

enum bibstate { inactive, error, active };
enum runstate { successful, unsuccessful };

class ClTitelsatz
{
public:
    ClTitelsatz();
    void laden(char *filename);
    void printT(); //print out all Titelsätze in Terminal
    void zeigeTitel(); //print out one Titelsätze in Terminal
    void saveSearch(ClBibliographie *current, ClBibliographie *save);
    void printF(ofstream &file); //print all Titelsätze in File

    enum runstate exportiere(char *action, ofstream &file, char *outputFile);
    enum runstate printF2(ofstream &file); //print last searchresult in File
    enum runstate sucheTitel(char *cat1, char *search1, char *cat2, char *search2, char *actionAndOr);
    enum runstate checkTag(char *toCheck);
    enum bibstate showstate() {return bibstate;};

    char *ISB(void){return current->ISB();};
    char *AUT(void){return current->AUT();};
    char *TIT(void){return current->TIT();};
    char *ORT(void){return current->ORT();};
    char *VLG(void){return current->VLG();};
    char *JAH(void){return current->JAH();};
    char *PR(void){return current->PR();};
    char *TIZ(void){return current->TIZ();};
    char *KOM(void){return current->KOM();};
    char *SLW(void){return current->SLW();};
    char *SIG(void){return current->SIG();};

    char *ISB2(void){return searchresult->ISB();};
    char *AUT2(void){return searchresult->AUT();};
    char *TIT2(void){return searchresult->TIT();};
    char *ORT2(void){return searchresult->ORT();};
    char *VLG2(void){return searchresult->VLG();};
    char *JAH2(void){return searchresult->JAH();};
    char *PR2(void){return searchresult->PR();};
    char *TIZ2(void){return searchresult->TIZ();};
    char *KOM2(void){return searchresult->KOM();};
    char *SLW2(void){return searchresult->SLW();};
    char *SIG2(void){return searchresult->SIG();};
private:
    ClBibliographie *root;
    ClBibliographie *current;

    ClBibliographie *searchresult;
    ClBibliographie *start;

    enum bibstate bibstate;
};
