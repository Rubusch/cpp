// Prog.cpp
/*
  Prueft ob eine Datumsangabe gueltig ist.
  Nur grob getestet.
//*/

#include <iostream>
using namespace std;

bool datumIstGueltig(int, int, int);

int main()
{
    int tag, monat, jahr;

    cout << "Das Programm kontrolliert ob ein eingegebenes Datum gueltig ist." << endl;
    cout << "Der wievielte Tag des Monats? ";
    cin >> tag;
    cout << "Der wievielte Monat? ";
    cin >> monat;
    cout << "Welches Jahr? ";
    cin >> jahr;

    if(datumIstGueltig(tag, monat, jahr))
        cout << "Das Datum ist gueltig." << endl;
    else
        cout << "Ungueltiges Datum!!!" << endl;

    return 0;
};


bool datumIstGueltig(int tag, int monat, int jahr)
{
    bool schaltjahr = false;

    // Monat gueltig?
    if( (monat < 0) || (monat > 12)) return false;

    // Jahr ist ein Schaltjahr?
    if( jahr < 0) return false;
    if( ((jahr%4 == 0) && (jahr%100 != 0)) || (jahr%400 == 0)) schaltjahr = true;

    // Tag gueltig?
    if( tag < 0) return false;

    if( (monat == 4) || (monat == 6) || (monat == 9) || (monat == 11)){
        if(tag > 30) return false;

    }else if( monat == 2){
        if( schaltjahr){
            if( tag > 29)
                return false;
        }else{
            if( tag > 28)
                return false;
        }

    }else{
        if(tag > 31) return false;
    }

    return true;
};

