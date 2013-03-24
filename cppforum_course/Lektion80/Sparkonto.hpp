// Sparkonto.hpp
/*
//*/

#ifndef SPARKONTO
#define SPARKONTO

#include "Konto.hpp"

class Sparkonto:public Konto
{
private:
public:
    Sparkonto();
    void anzeigen(); // virtual in "Konto"
    void jahresabschluss(); // rein virtual in "Konto"
    bool darfAuszahlen(double); // rein virtual in "Konto"
};

#endif
