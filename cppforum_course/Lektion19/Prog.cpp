// Prog.cpp
/*
  switch/case Beispiel
//*/

#include <iostream>
using namespace std;

int main()
{
    double zahl1;
    double zahl2;
    int operation;
    cout << "Volkards primitives Taschenrechner-Programm" << endl;
    cout << "Zahl1: ";
    cin >> zahl1;
    cout << "Zahl2: ";
    cin >> zahl2;
    cout << "Operation (1=+,2=-,3=*,4=/): ";
    cin >> operation;
    switch(operation){
    case 1:
        cout << zahl1 + zahl2 << endl;
        break;
    case 2:
        cout << zahl1 - zahl2 << endl;
        break;
    case 3:
        cout << zahl1 * zahl2 << endl;
        break;
    case 4:
        cout << zahl1 / zahl2 << endl; // wird implizit konvertiert in double
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0:
        cout << "Diese Ziffer ist nicht belegt." << endl;
        break;
    default:
        cout << "Das war noch nicht einmal eine Ziffer." << endl;
    };
    
    return 0;
};
