// Prog.cpp
/*
  Anwendung von Arrays.
//*/

#include <iostream>
using namespace std;

bool istDatumGueltig(int, int, int);
bool istSchaltjahr(int);


int main()
{
    int tag, monat, jahr;
    cout << "Monatstag: ";
    cin >> tag;
    cout << "Monatszahl: ";
    cin >> monat;
    cout << "Jahr: ";
    cin >> jahr;

    cout << "Das Datum ist " << (istDatumGueltig(tag,monat,jahr)?"gueltig":"ungueltig")
         << '.' << endl;

    return 0;
};


bool istDatumGueltig(int tag, int monat, int jahr)
{
    // gueltiger monat?
    if(monat<1 || monat>12) return false;

    // gueltiger tag?
    int tageImMonat[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(istSchaltjahr(jahr) && monat == 2){
        if(tag<1 || tag>29) return false;
    }else if(tag<1 || tag>tageImMonat[monat-1]){
        return false;
    };

    return true;
};


bool istSchaltjahr(int jahr)
{
    return (jahr%4==0 && jahr%100!=0) || jahr%400==0;
}

