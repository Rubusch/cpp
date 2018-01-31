// Prog.cpp
/*
//*/

#include <iostream>
using namespace std;

float berechneKegelvolumen(float r, float h)
{
    const float PI=3.14f;
    float g=PI*r*h;
    float v=(g*h)/3;

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

    return 0;
};

