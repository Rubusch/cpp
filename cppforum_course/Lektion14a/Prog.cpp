// Prog.cpp
/*
  break - herausspringen aus dem Loop
  continue - ans Ende des Blocks (weiter mit dem naechsten Schleifendurchgang)
//*/

#include <iostream>
using namespace std;

int main()
{
    int eingabe;
    int summe=0;

    do{
        cout << "Bitte geben Sie eine Zahl ein: ";
        cin >> eingabe;
        summe += eingabe;
    }while(eingabe != 0);
    cout << "Die Summe dieser Zahlen ist: " << summe << endl;

    return 0;
};

