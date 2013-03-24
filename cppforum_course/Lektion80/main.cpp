// main.cpp
/*
  Vererbungsbeispiel - Funktioniert jedoch nicht, wegen Polymorphie Problemen.
//*/

#include <iostream>
using namespace std;

#include "Konto.hpp"
#include "Girokonto.hpp"
#include "Sparkonto.hpp"

void inhaberUndKontoAnzeigen(string inhaber, Konto *pKto)
{
    cout << "Inhaber: " << inhaber << endl;
    pKto->anzeigen();
    cout << endl;
};


int main()
{
    Girokonto g;
    g.einzahlen(10);
    g.jahresabschluss();
    g.auszahlen(1000);
    g.auszahlen(100);
    g.anzeigen();
    
    Sparkonto s;
    s.einzahlen(200);
    s.jahresabschluss();
    s.auszahlen(1000);
    s.auszahlen(100);
    s.anzeigen();

    return 0;
};
