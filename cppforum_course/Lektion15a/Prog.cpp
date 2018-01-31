// Prog.cpp
/*
//*/

#include <iostream>
using namespace std;

int zugMensch(int);
int zugRechner(int);

int main()
{
    int anzahlDerMuenzen;

    // Eingabe der Anfangs-Muenzenanzahl
    cout << "Mit wievielen Muenzen fangen wir an? ";
    cin >> anzahlDerMuenzen;

    // Endlosschleife
    while(true){
        anzahlDerMuenzen = anzahlDerMuenzen - zugRechner(anzahlDerMuenzen);
        if(anzahlDerMuenzen == 0){
            cout << "Ich habe gewonnen!" << endl;
            return 0;
        }

        anzahlDerMuenzen = anzahlDerMuenzen - zugMensch(anzahlDerMuenzen);
        if(anzahlDerMuenzen == 0){
            cout << "Sie haben gewonnen!" << endl;
            return 0;
        }
    };

    return 0;
};


int zugMensch(int anzahlDerMuenzen)
{
    int ergebnis;

    cout << "Jetzt liegen " << anzahlDerMuenzen << " Muenzen auf dem Tisch." << endl;
    cout << "Wieviele moechten Sie nehmen? ";
    cin >> ergebnis;

    return ergebnis;
};


int zugRechner(int anzahlDerMuenzen)
{
    int wunschZug=anzahlDerMuenzen%4;
    if(wunschZug == 0)
        return 1;
    else
        return wunschZug;
};

