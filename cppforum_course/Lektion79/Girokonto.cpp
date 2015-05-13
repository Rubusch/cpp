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


void Girokonto::anzeigen() // virtual in Konto
{
    Konto::anzeigen();
    cout << "Ueberziehungsrahmen: " << ueberziehungsrahmen << endl;
};
