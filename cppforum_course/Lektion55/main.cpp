// main.cpp
/*
  Ein externer ueberladener Operator hat zwei (lhs und rhs) Parameter.
  Wird das eigene Objekt veraendert, muss eine Referenz zurueckgegeben
  werden.
  Bei cout<< ist das immer der Fall.
//*/

#include <iostream>
using namespace std;
#include "rational.h"

ostream &operator<<(ostream &out, Rational r)
{
    cout << r.m_zaehler << '/' << r.m_nenner;
    return cout;
};


int main()
{
    Rational a(1,2);
    Rational b(3,4);
    Rational c(5,6);
    Rational d(7,8);

    a=a+5;
    b=d+a;
    c=a*b;
    d=a+b;

    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;
    cout << "d=" << d << endl;

    return 0;
};



