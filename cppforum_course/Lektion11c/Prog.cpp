// Prog.cpp
/*
  Elegante Loesung - weniger if/else Bloecke.
//*/

#include <iostream>
using namespace std;

bool istSchaltjahr(int jahr)
{
    bool ist = false;

    if(jahr%4 == 0)
        ist = true;

    if(jahr%100 == 0) // Trick: hier muss == stehen!
        ist = false;

    if(jahr%400 == 0)
        ist = true;

    return ist;
};

int main()
{
    int jahr=0;
    cout << "Geben Sie eine Jahreszahl ein: ";
    cin >> jahr;
    if(istSchaltjahr(jahr))
        cout << "Das ist ein Schaltjahr." << endl;
    else
        cout << "Kein Schaltjahr!" << endl;

    return 0;
};

