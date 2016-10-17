#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;
#include <stdlib.h>
#include "titelsatz.h"

int main()
{
    char filename[64], action[64], actionCat1[64], actionSearch1[500], actionCat2[64], actionSearch2[500], outputFile[64], actionAndOr[64];
    ClTitelsatz bibliographies;

    cout << "Source file:" << endl;
    cin.getline(filename,64,'\n');
    bibliographies.laden(filename); //daten.txt = Testdatei "Brand.txt"

//    bibliographies.laden("daten.txt");

    if (bibliographies.showstate()!=active)
    {
        cout << "Error! '" << filename << "' could not be found." << endl;
        return 0;
    }

    for(;;)
    {
        cout << endl << "What would you like to do: " << endl <<
                " 'p' - print out converted source file" << endl <<
                " 'e' - export converted source file or last search result into output file" << endl <<
                " 's' - search source file" << endl <<
                " '*' - exit prgorgram" << endl;
        cin.getline(action, 64, '\n');

        switch(action[0])
        {
        case 'p':
                bibliographies.printT();
            break;
        case 'e':
        {
            cout << endl << "Output file: " << endl;
            cin.getline(outputFile, 64, '\n');
            ofstream file (outputFile);

            cout << endl << "What would you like to export?" << endl <<
                   " 'w' - whole source file" << endl <<
                   " 's' - last search result" << endl;
            cin.getline(action, 64, '\n');

            bibliographies.exportiere(action, file, outputFile);

            file.close();
            break;
        }
        case 's':
        {
            for(;;)
            {
                actionAndOr[0]='\n';

                cout << endl << "Enter a category: ";
                cin.getline(actionCat1, 64, '\n');
                if (bibliographies.checkTag(actionCat1)!=successful)
                {
                    cout << endl << "Illegal category! \nPlease choose one of the following: "
                                    "\nISB, AUT, TIT, ORT, VLG, JAH, PR, TIZ, KOM, SLW, SIG, "
                                    "\n*020$a, *100$a, *245$a, *260$a, *260$b, *260$c, *365$b, *500$a, *500$a, *653$a, *852$c" << endl;
                    break;
                }

                cout << "Enter a search term: ";
                cin.getline(actionSearch1, 500, '\n');
                cout << endl;

                cout << endl << "Include a search in a second category?" << endl <<
                        " 'y' " << endl <<
                        " 'n' " << endl;
                cin.getline(action, 64, '\n');
                cout << endl;

                switch(action[0])
                {
                case 'y':
                {
                    cout << "Enter a 2nd category: ";
                    cin.getline(actionCat2, 64, '\n');
                    if (strlen(actionCat2) != 0)
                    {
                        if (bibliographies.checkTag(actionCat2)!=successful)
                        {
                            cout << endl << "Illegal category! \nPlease choose one of the following: "
                                            "\nISB, AUT, TIT, ORT, VLG, JAH, PR, TIZ, KOM, SLW, SIG, "
                                            "\n*020$a, *100$a, *245$a, *260$a, *260$b, *260$c, *365$b, *500$a, *500$a, *653$a, *852$c" << endl;
                            break;
                        }
                    }
                    else
                        goto no;

                    cout << "Enter a 2nd search term: ";
                    cin.getline(actionSearch2, 500, '\n');
                    cout << endl;

                    cout << endl << "Would you like to search for 'Titelsätze' that: " << endl <<
                           " '&' -  match both, catergories and search terms" << endl <<
                           " '|' - match one of the catergories and search terms" << endl;
                    cin.getline(actionAndOr, 64, '\n');
                    cout << endl;

                    if (strncmp(actionAndOr,"&",1)!=0 && strncmp(actionAndOr,"|",1)!=0 )
                    {
                        cout << endl << "Illegal action" << endl;
                        break;
                    }

                    if (bibliographies.sucheTitel(actionCat1, actionSearch1, actionCat2, actionSearch2, actionAndOr)==unsuccessful)
                             cout << "No match found." << endl;
                   break;
                }
                no:
                case 'n':
                {
                    if (bibliographies.sucheTitel(actionCat1, actionSearch1, actionCat2, actionSearch2, actionAndOr)==unsuccessful)
                         cout << "No match found." << endl;
                    break;
                }
                default:
                    cout << "Please choose one of the given actions!" << endl;
                    break;
                }
                break;
            }
            break;
        }
        case '*':
            return 0;
        default:
            cout << "Please choose one of the given actions!" << endl;
            break;
        }
    }
}
