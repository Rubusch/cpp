// Girokonto.hpp
/*
//*/

#ifndef GIROKONTO
#define GIROKONTO

#include "Konto.hpp"

class Girokonto:public Konto
{
private:
    double ueberziehungsrahmen;

public:
    Girokonto();
    void anzeigen(); // virtual in "Konto"
    bool darfAuszahlen(double); // rein virtual in "Konto"
    void jahresabschluss(); // rein virtual in "Konto"
};

#endif
