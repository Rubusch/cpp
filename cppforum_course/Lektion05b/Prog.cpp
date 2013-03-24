// Prog.cpp
/*
//*/

#include <iostream>
using namespace std;

int main()
{
    float radius;
    float hoehe;
    cout << "Bitte geben Sie den Radius ein: ";
    cin >> radius;
    cout << "Bitte geben sie die Hoehe ein: ";
    cin >> hoehe;
    const float PI=3.14f;
    float grundflaeche=PI*radius*radius;
    float volumen=(grundflaeche*hoehe)/3;
    cout << "Das Volumen betraegt: " << volumen << endl;
    
    return 0;
};
