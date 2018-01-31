// Prog.cpp
/*
//*/

#include <iostream>
using namespace std;

int main()
{
    const float LIMIT=80;
    float geschwindigkeit;
    cout << "Bitte geben Sie die Geschwindigkeit ein: ";
    cin >> geschwindigkeit;
    if(geschwindigkeit > LIMIT)
        if(geschwindigkeit > LIMIT+30)
            cout << "Zu schnell gefahren. Punkte in Flensburg!" << endl;
        else
            cout << "Zu schnell gefahren. Verwarnungsgeld!" << endl;
    else
        cout << "Nicht zu schnell gefahren." << endl;

    return 0;
};
