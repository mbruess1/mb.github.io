#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;
#include <stdlib.h>
#include "bibliographie.h"

ClBibliographie::ClBibliographie(ifstream &inputFile)
{
    char buffer [500], character;
    int counter;
    enum state state;

    next=NULL;
    next2=NULL;
    *eISB='\0', *eAUT='\0', *eTIT='\0', *eORT='\0', *eVLG='\0', *eJAH='\0', *ePR='\0', *eTIZ='\0', *eKOM='\0', *eSLW='\0', *eSIG='\0';
    state=abbr;
    counter=0;

    for(;;)
    {
        inputFile.get(character);
        if (inputFile.eof()) // end of file / last entry
        {
            buffer[counter]='\0';
            counter=0;
            switch (eposition)
            {
            case 0:
                strcpy(eISB,buffer);
                break;
            case 1:
                strcpy(eAUT,buffer);
                break;
            case 2:
                strcpy(eTIT,buffer);
                break;
            case 3:
                strcpy(eORT,buffer);
                break;
            case 4:
                strcpy(eVLG,buffer);
                break;
            case 5:
                strcpy(eJAH,buffer);
                break;
            case 6:
                strcpy(ePR,buffer);
                break;
            case 7:
                strcpy(eTIZ,buffer);
                break;
            case 8:
                strcpy(eKOM,buffer);
                break;
            case 9:
                strcpy(eSLW,buffer);
                break;
            case 10:
                strcpy(eSIG,buffer);
                break;
            default:
                return;
            }
            return;
        }
        switch(character)
        {
        case '\n':
            inputFile.get(character);
            if (inputFile.eof()) return;
            else if (character!=' ' && state==entry) //end of entry
            {
                buffer[counter]='\0';
                counter=0;
                switch (eposition)
                {
                case 0:
                    strcpy(eISB,buffer);
                    break;
                case 1:
                    strcpy(eAUT,buffer);
                    break;
                case 2:
                    strcpy(eTIT,buffer);
                    break;
                case 3:
                    strcpy(eORT,buffer);
                    break;
                case 4:
                    strcpy(eVLG,buffer);
                    break;
                case 5:
                    strcpy(eJAH,buffer);
                    break;
                case 6:
                    strcpy(ePR,buffer);
                    break;
                case 7:
                    strcpy(eTIZ,buffer);
                    break;
                case 8:
                    strcpy(eKOM,buffer);
                    break;
                case 9:
                    strcpy(eSLW,buffer);
                    break;
                case 10:
                    strcpy(eSIG,buffer);
                    break;
                default:
                    break;
                }
                inputFile.putback(character);
                state=abbr;
            }
            else if (character==' ' && state==entry) //continue entry
            {
                for (; character== ' '; inputFile.get(character)) //delete white spaces
                    continue;
                inputFile.putback(character);
            }
            else if (character=='\n' && state==abbr) //line breaks
                return;
            else
            {
                inputFile.putback(character);
                return;
            }
            break;
        case '=':
            inputFile.get(character);
            if (character== '=' && state == abbr)
            {
                buffer[counter]='\0';
                counter+=3;

                const char *oldArray[11] = {"ISB", "AUT", "TIT", "ORT", "VLG", "JAH", "PR", "TIZ", "KOM", "SLW", "SIG"};
                const char *newArray[11] = {"*020$a", "*100$a", "*245$a", "*260$a", "*260$b", "*260$c", "*365$b", "*500$a", "*500$a", "*653$a", "*852$c"};

                for (int i=0; i < 11; i++) {     //convert from old to new
                    if(strcmp(buffer,oldArray[i])==0)
                    {
                         strcpy(buffer,newArray[i]);
                         eposition = i;
                    }
                }
                state=entry;
            }
            else
                inputFile.putback(character);
            break;
        default:
            buffer[counter]=character;
            counter++;
            break;
        }
    }
}

ClBibliographie *ClBibliographie::entryresult(char *cat1, char *search1, char *cat2, char *search2, char *actionAndOr)
{
        string check1, check2;
        if (strcmp(cat1, "ISB")==0 || strcmp(cat1, "*020$a")==0)
            check1 =eISB;
        else if (strcmp(cat1, "AUT")==0 || strcmp(cat1, "*100$a") ==0)
            check1 = eAUT;
        else if (strcmp(cat1, "TIT")==0 || strcmp(cat1, "*245$a")==0)
            check1 = eTIT;
        else if (strcmp(cat1, "ORT")==0 || strcmp(cat1, "*260$a")==0)
            check1 = eORT;
        else if (strcmp(cat1, "VLG")==0 || strcmp(cat1, "*260$b")==0)
            check1 = eVLG;
        else if (strcmp(cat1, "JAH")==0 || strcmp(cat1, "*260$c")==0 )
            check1 = eJAH;
        else if (strcmp(cat1, "PR")==0 || strcmp(cat1, "*365$b")==0)
            check1 = ePR;
        else if (strcmp(cat1, "TIZ")==0 || strcmp(cat1, "*500$a")==0)
            check1 = eTIZ;
        else if (strcmp(cat1, "KOM")==0 || strcmp(cat1, "*500$a")==0)
            check1 = eKOM;
        else if (strcmp(cat1, "SLW")==0 || strcmp(cat1, "*653$a")==0)
            check1 = eSLW;
        else if (strcmp(cat1, "SIG")==0 || strcmp(cat1, "*852$c")==0)
            check1 = eSIG;
        else
            check1 ="\0";

        if (strcmp(cat2, "ISB")==0 || strcmp(cat2, "*020$a")==0)
            check2 =eISB;
        else if (strcmp(cat2, "AUT")==0 || strcmp(cat2, "*100$a") ==0)
            check2 = eAUT;
        else if (strcmp(cat2, "TIT")==0 || strcmp(cat2, "*245$a")==0)
            check2 = eTIT;
        else if (strcmp(cat2, "ORT")==0 || strcmp(cat2, "*260$a")==0)
            check2 = eORT;
        else if (strcmp(cat2, "VLG")==0 || strcmp(cat2, "*260$b")==0)
            check2 = eVLG;
        else if (strcmp(cat2, "JAH")==0 || strcmp(cat2, "*260$c")==0 )
            check2 = eJAH;
        else if (strcmp(cat2, "PR")==0 || strcmp(cat2, "*365$b")==0)
            check2 = ePR;
        else if (strcmp(cat2, "TIZ")==0 || strcmp(cat2, "*500$a")==0)
            check2 = eTIZ;
        else if (strcmp(cat2, "KOM")==0 || strcmp(cat2, "*500$a")==0)
            check2 = eKOM;
        else if (strcmp(cat2, "SLW")==0 || strcmp(cat2, "*653$a")==0)
            check2 = eSLW;
        else if (strcmp(cat2, "SIG")==0 || strcmp(cat2, "*852$c")==0)
            check2 = eSIG;
        else
            check2 ="\0";

        int searchterm1 = check1.find(search1);
        int searchterm2 = check2.find(search2);

        switch(actionAndOr[0])
        {
        case '&':
            if (searchterm1 >= 0 && searchterm2 >= 0)
                return this;
            if (next==NULL)
                return NULL;
            break;
        case '|':
            if (searchterm1 >= 0 || searchterm2 >= 0)
                return this;
            if (next==NULL)
                return NULL;
            break;
         default:
            if (searchterm1 >= 0)
                return this;
            if (next==NULL)
                return NULL;
            break;
        }
        check1 = "\0";
        check2 ="\0";
        searchterm1 = 0;
        searchterm2 = 0;
        return next->entryresult(cat1, search1, cat2, search2, actionAndOr);
}
