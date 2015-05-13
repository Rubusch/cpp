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
    kontostand -= auszahlung;
};


void Konto::anzeigen()
{
    cout << "Kontostand: " << kontostand << endl;
};
