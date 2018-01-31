// Sparkonto.cpp
/*
//*/


#include <iostream>
using namespace std;

#include "Sparkonto.hpp"


Sparkonto::Sparkonto()
{

};


void Sparkonto::anzeigen() // virtual in "Konto"
{
    Konto::anzeigen();
};


bool Sparkonto::darfAuszahlen(double auszahlung) // rein virtual in "Konto"
{
    return (kontostand-auszahlung) > 0;
};


void Sparkonto::jahresabschluss() // rein virtual in "Konto"
{
    kontostand += 0.1*kontostand;
};


