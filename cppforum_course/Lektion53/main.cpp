// main.cpp
/*
  Die Klasse Rational stellt einen Bruch dar.
//*/

#include <iostream>
using namespace std;
#include "rational.h"

int main()
{
    Rational a(2,4);
    cout << "a = ";
    a.print();
    cout << endl;

    Rational b(1,3);
    cout << "b = ";
    b.print();
    cout << endl;

    Rational c=a*b;
    cout << "c = a*b = ";
    c.print();
    cout << endl;

    Rational d=a+b;
    cout << "d = a+b = ";
    d.print();
    cout << endl;
    
    Rational e=a-b;
    cout << "e = a-b = ";
    e.print();
    cout << endl;
    
    Rational f=a/b;
    cout << "f = a/b = ";
    f.print();
    cout << endl;

    return 0;
};



