// Konto.hpp
/*
//*/

#ifndef KONTO
#define KONTO

class Konto
{
protected:
    double kontostand;

public:
    Konto();
    void einzahlen(double einzahlung);
    void auszahlen(double auszahlung);
    virtual void anzeigen();
};

#endif
