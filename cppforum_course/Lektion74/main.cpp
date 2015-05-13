// main.cpp
/*
  Nichtfunktionierende Version - sh. naechstes Kapitel
//*/

#include <iostream>
#include <string>
using namespace std;

#include "SortedArray.h"
#include "DefaultComparator.h"
#include "Dictionary.h"

int main()
{
    Dictionary< string, string > buch;
    bool nochmal = true;
    while(nochmal){
        cout << "Menu" << endl;
        cout << "1 : Name einfuegen" << endl;
        cout << "2 : Name suchen" << endl;
        cout << "3 : Name aendern" << endl;
        cout << "4 : Name loeschen" << endl;
        cout << "5 : Liste anzeigen" << endl;
        cout << "0 : Programm beenden" << endl;
        int eingabe;
        cin >> eingabe;
        
        string name;
        string nummer;
        switch(eingabe){
        case 0:
            nochmal = false;
            break;

        case 1: // Name einfuegen
            cin >> name;
            cin >> nummer;
            buch.insert(name, nummer);
            break;
            
        case 2: // Name suchen
            break;
            
        case 3: // Name aendern
            break;
            
        case 4: // Name loeschen
            break;
            
        case 5: // Liste anzeigen
            break;
            
        default:
            cout << "Diesen Menupunkt gibt es nicht!" << endl;
        };
    };

    return 0;
};
