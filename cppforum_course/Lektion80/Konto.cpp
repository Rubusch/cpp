// Konto.cpp
/*
//*/

#include <iostream>
using namespace std;

#include "Konto.hpp"

Konto::Konto()
{
    kontostand = 0;
};


void Konto::einzahlen(double einzahlung)
{
    kontostand += einzahlung;
};


void Konto::auszahlen(double auszahlung)
{
    if(darfAuszahlen(auszahlung))
        kontostand -= auszahlung;
    else cout << "Auszahlung nicht moeglich!" << endl;
};


void Konto::anzeigen()
{
    cout << "Kontostand: " << kontostand << endl;
};
