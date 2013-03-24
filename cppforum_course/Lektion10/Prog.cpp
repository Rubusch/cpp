// Prog.cpp
/*
  Kein ';' nach einem Block im Code!!!
//*/

#include <iostream>
using namespace std;

int main()
{
    const float LIMIT=80;
    float geschwindigkeit;
    cout << "Bitte geben Sie die Geschwindigkeit ein: ";
    cin >> geschwindigkeit;
    if(geschwindigkeit > LIMIT){
        cout << "Zu schnell gefahren.";
        if(geschwindigkeit > LIMIT+30)
            cout << "Punkte in Flensburg!" << endl;
        else
            cout << "Verwarnungsgeld!" << endl;
    } // Hier darf kein ';' stehen, sonst immer!!!
    else
        cout << "Nicht zu schnell gefahren." << endl;
};
