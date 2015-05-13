// Prog.cpp
/*
  if abfackeln mit einem zusaetzlichen else ;
//*/

#include <iostream>
using namespace std;

int main()
{
    const float LIMIT=80;
    float geschwindigkeit;
    cout << "Bitte geben Sie die Geschwindigkeit ein: ";
    cin >> geschwindigkeit;
    if(geschwindigkeit>LIMIT)
        if(geschwindigkeit > LIMIT + 30)
            cout << "Zu schnell gefahren. Punkte in Flensburg!" << endl;
        else
            ; // notwendig, da sich else immer auf das letzte if bezieht
    else
        cout << "Nicht zu schnell gefahren." << endl;

    return 0;
};
