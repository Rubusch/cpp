// main.cpp
/*
  Bringt das Programm immer noch zum abstuerzen 
  -> Zuweisungsoperator ist noch nicht ueberladen.
//*/

#include <iostream>
using namespace std;

#include "vector.h"

int main()
{
    Vector v1(10);
    v1[1] = 4711;
    v1[2] = 0;
    Vector v2(10);
    v2 = v1;
    v2[2] = 4712;
    cout << v1[1] << endl;
    cout << v1[2] << endl;
};

