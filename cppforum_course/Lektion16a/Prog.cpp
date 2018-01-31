// Prog.cpp
/*
  Berechnung der Fibonacci-Zahlen: iterativ.
//*/

#include <iostream>
using namespace std;

int main()
{
    int limit=1;
    int zahl=1;
    int vorgaenger1=0;
    int vorgaenger2=0;

    cout << "Bis zu welcher Zahl sollen die Fibonacci-Zahlen berechnet werden? ";
    cin >> limit;

    while(zahl<=limit){
        cout << zahl << endl;

        vorgaenger1 = zahl;
        zahl = vorgaenger1 + vorgaenger2;
        vorgaenger2 = vorgaenger1;
    };

    return 0;
};
