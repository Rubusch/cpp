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


void Girokonto::anzeigen()
{
    cout << "Kontostand: " << kontostand << endl;
    cout << "Ueberziehungsrahmen: " << ueberziehungsrahmen << endl;
};
