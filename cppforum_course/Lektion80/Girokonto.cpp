// Girokonto.cpp
/*
//*/

#include <iostream>
using namespace std;

#include "Girokonto.hpp"
#include "Konto.hpp"

Girokonto::Girokonto()
{
    ueberziehungsrahmen = 1000;
};


void Girokonto::anzeigen() // virtual in "Konto"
{
    Konto::anzeigen();
    cout << "Ueberziehungsrahmen: " << ueberziehungsrahmen << endl;
};


bool Girokonto::darfAuszahlen(double auszahlung) // rein virtual in "Konto"
{
    return (kontostand + ueberziehungsrahmen - auszahlung) > 0;
};


void Girokonto::jahresabschluss()
{
    if(kontostand > 0)
        kontostand += 0.1 * kontostand;
};
