// Girokonto.hpp
/*
//*/

#ifndef GIROKONTO
#define GIROKONTO

class Girokonto:public Konto
{
private:
    double ueberziehungsrahmen;

public:
    Girokonto();
    void anzeigen();
};

#endif
