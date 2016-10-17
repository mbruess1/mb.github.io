#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;
#include <stdlib.h>
#include "titelsatz.h"

ClTitelsatz::ClTitelsatz()
{
    root=NULL;
    current=NULL;
    bibstate=inactive;

    searchresult=NULL;
    start=NULL;
}

void ClTitelsatz::laden(char *filename)
{
    ifstream inputFile;
    inputFile.open(filename);

    if (!inputFile)
    {
        bibstate=error;
        return;
    }

    ClBibliographie *nouveau;

    while(!inputFile.eof())
    {
        nouveau = new ClBibliographie(inputFile); //read 1 line
        if (nouveau->ISB()[0]!='\0' || nouveau->AUT()[0]!='\0' || nouveau->TIT()[0]!='\0'  || nouveau->ORT()[0]!='\0' || nouveau->VLG()[0]!='\0'  || nouveau->JAH()[0]!='\0' || nouveau->PR()[0]!='\0' || nouveau->TIZ()[0]!='\0' || nouveau->KOM()[0]!='\0' || nouveau->SLW()[0]!='\0' || nouveau->SIG()[0]!='\0')
        {
            if (root==NULL)
                root=nouveau;
            else
                current->connectentry(nouveau);
            current=nouveau;
        }
    }
    inputFile.close();

    if (root==NULL)
        bibstate=error;
    else
        bibstate=active;
    current=root;
}

void ClTitelsatz::saveSearch(ClBibliographie *current, ClBibliographie *save)
{
    save=current;
    if (start==NULL)
        start=save;
    else
        searchresult->connectentry2(save);
    searchresult=save;
}

ClBibliographie *save = new ClBibliographie();
enum runstate ClTitelsatz::sucheTitel(char *cat1, char *search1, char *cat2, char *search2, char *actionAndOr)
{
    save=NULL;
    searchresult=NULL;
    start=NULL;

    current=current->entryresult(cat1, search1, cat2, search2, actionAndOr);
    if (current==NULL)
    {
        current=root;
        return unsuccessful;
    }
    else
    {
        while (current!=NULL)
        {
            zeigeTitel();
            saveSearch(current, save);

            current=current->next;
            if (current==NULL)
            {
                break;
            }
            current=current->entryresult(cat1, search1, cat2, search2, actionAndOr);
        }
        current=root;
        searchresult->connectentry2(NULL); //stops appending old results, that have sth in common with new results to export of later
        searchresult=start;
        return successful;
    }
}

enum runstate ClTitelsatz::checkTag(char *toCheck)
{
    const char *oldArray[11] = {"ISB", "AUT", "TIT", "ORT", "VLG", "JAH", "PR", "TIZ", "KOM", "SLW", "SIG"};
    const char *newArray[11] = {"*020$a", "*100$a", "*245$a", "*260$a", "*260$b", "*260$c", "*365$b", "*500$a", "*500$a", "*653$a", "*852$c"};

    for (int i=0; i < 10; i++) {
        if(strcmp(toCheck,oldArray[i])==0 || strcmp(toCheck,newArray[i])==0)
            return successful;
    }
    return unsuccessful;
}

void ClTitelsatz::printT()
{
    while(current!=NULL)
    {
        if(strlen(ISB()) != 0)
            cout << ISB() << endl;
        if(strlen(AUT()) != 0)
            cout << AUT() << endl;
        if(strlen(TIT()) != 0)
            cout << TIT() << endl;
        if(strlen(ORT()) != 0)
            cout << ORT() << endl;
        if(strlen(VLG()) != 0)
            cout << VLG() << endl;
        if(strlen(JAH()) != 0)
            cout << JAH() << endl;
        if(strlen(PR()) != 0)
            cout << PR() << endl;
        if(strlen(TIZ()) != 0)
            cout << TIZ() << endl;
        if(strlen(KOM()) != 0)
            cout << KOM() << endl;
        if(strlen(SLW()) != 0)
            cout << SLW() << endl;
        if(strlen(SIG()) != 0)
            cout << SIG() << endl;
        cout << endl;
        current=current->next;
    }
    current=root;
}

void ClTitelsatz::zeigeTitel()
{
    if(strlen(ISB()) != 0)
        cout << ISB() << endl;
    if(strlen(AUT()) != 0)
        cout << AUT() << endl;
    if(strlen(TIT()) != 0)
        cout << TIT() << endl;
    if(strlen(ORT()) != 0)
        cout << ORT() << endl;
    if(strlen(VLG()) != 0)
        cout << VLG() << endl;
    if(strlen(JAH()) != 0)
        cout << JAH() << endl;
    if(strlen(PR()) != 0)
        cout << PR() << endl;
    if(strlen(TIZ()) != 0)
        cout << TIZ() << endl;
    if(strlen(KOM()) != 0)
        cout << KOM() << endl;
    if(strlen(SLW()) != 0)
        cout << SLW() << endl;
    if(strlen(SIG()) != 0)
        cout << SIG() << endl;
    cout << endl;
}

runstate ClTitelsatz::exportiere(char *action, ofstream &file, char *outputFile)
{
    switch(action[0])
    {
    case 'w':
    {
        printF(file);
        if(!file.bad())
        {
            cout << "Output in '" << outputFile << "' completed." << endl;
            return successful;
        }
        else
            return unsuccessful;
        break;
    }
    case 's':
    {
        if (printF2(file)==unsuccessful)
        {
            cout << endl << "No search results available" << endl;
            remove(outputFile);
            return unsuccessful;
        }

        if(!file.bad())
        {
            cout << endl << "Output in '" << outputFile << "' completed." << endl;
            return successful;
        }
        else
            return unsuccessful;
        break;
    }
    default:
        cout << endl << "Illegal action" << endl;
        remove(outputFile);
        return unsuccessful;
        break;
    }
}

void ClTitelsatz::printF(ofstream &file)
{
    while(current!=NULL)
    {
        if(strlen(ISB()) != 0)
            file << ISB() << endl;
        if(strlen(AUT()) != 0)
            file << AUT() << endl;
        if(strlen(TIT()) != 0)
            file << TIT() << endl;
        if(strlen(ORT()) != 0)
            file << ORT() << endl;
        if(strlen(VLG()) != 0)
            file << VLG() << endl;
        if(strlen(JAH()) != 0)
            file << JAH() << endl;
        if(strlen(PR()) != 0)
            file << PR() << endl;
        if(strlen(TIZ()) != 0)
            file << TIZ() << endl;
        if(strlen(KOM()) != 0)
            file << KOM() << endl;
        if(strlen(SLW()) != 0)
            file << SLW() << endl;
        if(strlen(SIG()) != 0)
            file << SIG() << endl;
        file << endl;
        current=current->next;
    }
    current=root;
}

runstate ClTitelsatz::printF2(ofstream &file)
{
    if (searchresult==NULL)
        return unsuccessful;
    while(searchresult!=NULL)
    {
        if(strlen(ISB2()) != 0)
            file << ISB2() << endl;
        if(strlen(AUT2()) != 0)
            file << AUT2() << endl;
        if(strlen(TIT2()) != 0)
            file << TIT2() << endl;
        if(strlen(ORT2()) != 0)
            file << ORT2() << endl;
        if(strlen(VLG2()) != 0)
            file << VLG2() << endl;
        if(strlen(JAH2()) != 0)
            file << JAH2() << endl;
        if(strlen(PR2()) != 0)
            file << PR2() << endl;
        if(strlen(TIZ2()) != 0)
            file << TIZ2() << endl;
        if(strlen(KOM2()) != 0)
            file << KOM2() << endl;
        if(strlen(SLW2()) != 0)
            file << SLW2() << endl;
        if(strlen(SIG2()) != 0)
            file << SIG2() << endl;
        file << endl;
        searchresult=searchresult->next2;
    }
    searchresult=start;
    return successful;
}
