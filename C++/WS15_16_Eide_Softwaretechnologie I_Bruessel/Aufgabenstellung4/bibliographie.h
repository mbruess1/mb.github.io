#include <fstream>

enum state {abbr, entry};

class ClBibliographie
{
public:
    int eposition;
    ClBibliographie() {next=NULL; next2=NULL;}
    ClBibliographie(ifstream &inputFile);
    ClBibliographie *entryresult(char *cat1, char *search1, char *cat2, char *search2, char *actionAndOr); //returns search results to sucheTitel()

    char *ISB(void){return eISB;}
    char *AUT(void){return eAUT;}
    char *TIT(void){return eTIT;}
    char *ORT(void){return eORT;}
    char *VLG(void){return eVLG;}
    char *JAH(void){return eJAH;}
    char *PR(void){return ePR;}
    char *TIZ(void){return eTIZ;}
    char *KOM(void){return eKOM;}
    char *SLW(void){return eSLW;}
    char *SIG(void){return eSIG;}

    ClBibliographie *next, *next2;
    void connectentry(ClBibliographie *nouveau) {next=nouveau;}
    void connectentry2(ClBibliographie *save) {next2=save;}
private:
    char eISB[500], eAUT[500], eTIT[500], eORT[500], eVLG[500], eJAH[500], ePR[500], eTIZ[500], eKOM[500], eSLW[500], eSIG[500];
};
