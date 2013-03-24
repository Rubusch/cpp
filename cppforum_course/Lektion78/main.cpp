// main.cpp
/*
  Vererbungsbeispiel - Funktioniert jedoch nicht, wegen Polymorphie Problemen.
//*/

#include <iostream>
using namespace std;

#include "Konto.hpp"
#include "Girokonto.hpp"

void inhaberUndKontoAnzeigen(string inhaber, Konto *pKto)
{
    cout << "Inhaber: " << inhaber << endl;
    pKto->anzeigen();
    cout << endl;
};


int main()
{
    Konto k;
    Girokonto g;
    k.anzeigen();
    cout << endl;
    
    g.anzeigen();
    cout << endl;

    inhaberUndKontoAnzeigen("Volkard", &k);
    inhaberUndKontoAnzeigen("Wolfram", &g);

    return 0;
};
