// Prog.cpp
/*
  float Zahlen und implizite int Zahlen und Modulo Operator!
//*/

#include <iostream>
using namespace std;

float berechneKegelvolumen(float r, float h)
{
    const float PI=3.14f;
    float g=PI*r*h;
    float v=1.0/3.0*g*h; // 1.0 und 3.0, mit 1 und 3 waere das Ergebnis 0

    return v;
};

int main()
{
    float radius;
    float hoehe;
    cout << "Bitte geben Sie den Radius ein: ";
    cin >> radius;
    cout << "Bitte geben Sie die Hoehe ein: ";
    cin >> hoehe;
    cout << "Das Volumen betraegt: " << berechneKegelvolumen(radius, hoehe) << endl;

    cout << "Berechnung des Modulo Operators" << endl;
    cout << "Ganzes Zahl Ergebnis 25/7: " << 25/7 << endl;
    cout << "(25/7)*7: " << (25/7)*7 << endl;
    cout << "25 - ((25/7)*7): " << 25-((25/7)*7) << endl;
    cout << "25.0/7.0: " << 25.0/7.0 << endl;
    cout << "25%7: " << 25%7 << " -> Modulo == Rest" << endl;

    return 0;
};

