// Prog.cpp
/*
  Nimm 1,2 oder 3 Spiel

  Version mit abgesicherter Eingabe und Angabe wieviele Muenzen der Rechner zieht.
//*/

#include <iostream>
using namespace std;

int zugRechner(int);
int zugMensch(int);

int main()
{
    int anzahlDerMuenzen;
    int cnt=0;

    // Eingabe der Anfangs-Muenzenahl
    cout << "Mit wievielen Muenzen fangen wir an? ";
    cin >> anzahlDerMuenzen;

    // Endlosschleife
    while(true){
        ++cnt;
        int rechnerNimmt = zugRechner(anzahlDerMuenzen);
        cout << '\n' <<  cnt << ". Ich nehme " << rechnerNimmt
             << ((rechnerNimmt==1)?" Muenze.":" Muenzen.")
             << endl;
        anzahlDerMuenzen = anzahlDerMuenzen - rechnerNimmt;
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
    int ergebnis=4;
    cout << "Jetzt liegen " << anzahlDerMuenzen << " Muenzen auf dem Tisch." << endl;
    while( (ergebnis > 3) || (ergebnis < 1)){
        cout << "Wieviele moechten Sie nehmen? ";
        cin >> ergebnis;
        if((ergebnis < 1) || (ergebnis > 3))
            cout << "Sie duerfen nur 1, 2 oder 3 Muenzen nehmen!" << endl;
        if(ergebnis > anzahlDerMuenzen){
            cout << "So viele Muenzen liegen nicht mehr auf dem Tisch herum!" << endl;
            ergebnis=4;
        }
    };

    return ergebnis;
};


int zugRechner(int anzahlDerMuenzen)
{
    int wunschZug = anzahlDerMuenzen % 4;
    if(wunschZug == 0)
        return 1;
    else
        return wunschZug;
};

