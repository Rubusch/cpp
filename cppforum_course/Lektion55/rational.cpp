// rational.cpp
/*
  Typumwandlungskonstruktor.
//*/
#include <iostream>
#include "rational.h"

Rational::Rational(int zaehler, int nenner)
{
    m_zaehler = zaehler;
    m_nenner = nenner;
    kuerzen();
};


Rational::Rational(int zahl)
{
    m_zaehler = zahl;
    m_nenner = 1;
};


void Rational::kuerzen()
{
    int ggtVar = ggt(m_zaehler, m_nenner);
    m_zaehler/=ggtVar;
    m_nenner/=ggtVar;
};


int Rational::ggt(int a, int b)
{
    int tmp=0;
    a = abs(a);
    b = abs(b);
    
    if(a>b) swap(&a, &b);
        
    while(b!=0){
        tmp=a;
        a=b;
        b=tmp%b;
    }
    return a;
};


int Rational::kgv(int a, int b)
{
    return a*b/ggt(a,b);
};


void Rational::swap(int *a, int *b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
};


Rational Rational::operator*(Rational rhs)
{
    int resultZaehler = m_zaehler * rhs.m_zaehler;
    int resultNenner = m_nenner * rhs.m_nenner;
    Rational result(resultZaehler, resultNenner);
    return result;
};


Rational Rational::operator+(Rational rhs)
{
    int resultZaehler = m_zaehler * rhs.m_nenner + rhs.m_zaehler * m_nenner;
    int resultNenner = m_nenner * rhs.m_nenner;
    Rational result(resultZaehler, resultNenner);
    return result;
};


Rational Rational::operator-(Rational rhs)
{
    int resultZaehler = m_zaehler * rhs.m_nenner - rhs.m_zaehler * m_nenner;
    int resultNenner = m_nenner * rhs.m_nenner;
    Rational result(resultZaehler, resultNenner);
    return result;
};


Rational Rational::operator/(Rational rhs)
{
    int resultZaehler = m_zaehler * rhs.m_nenner;
    int resultNenner = m_nenner * rhs.m_zaehler;
    Rational result(resultZaehler, resultNenner);
    return result;
};


void Rational::print()
{
    std::cout << m_zaehler << '/' << m_nenner;
};

