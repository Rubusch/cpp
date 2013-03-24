// Prog.cpp
/*
  Referenzen sind Zeiger, die so tun als waeren sie die Variable auf die sie zeigen.
  (Besser ist hier trotzdem mit den Zeigern zu arbeiten).
//*/

#include <iostream>
using namespace std;

int main()
{
    int a=1;
    int &ra=a;
    cout << "a: " << a << endl;
    ra=2;
    cout << "a: " << a << endl;
};

