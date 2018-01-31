// Prog.cpp
/*
  Nimm 1,2 oder 3 Spiel

  Hier die Version bei der derjenige verloren hat der zuletzt zieht.
  Es wird angegeben wieviele Muenzen der Rechner zieht.
  Die Eingabe ist eingeschraenkt auf 1,2 oder 3 Muenzen.
  Der Modulo verschiebt sich um eine Einheit.
  Die Gewinnmeldungen wurden ebenfalls vertauscht.
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
        int zug = zugRechner(anzahlDerMuenzen);
        cout << "\nIch nehme " << zug << ((zug==1)?" Muenze.":" Muenzen") << endl;
        anzahlDerMuenzen -= zug;
        if(anzahlDerMuenzen == 0){
            cout << "Sie haben gewonnen!" << endl;
            return 0;
        }

        anzahlDerMuenzen -= zugMensch(anzahlDerMuenzen);
        if(anzahlDerMuenzen == 0){
            cout << "Ich habe gewonnen!" << endl;
            return 0;
        }
    };

    return 0;
};


int zugMensch(int anzahlDerMuenzen)
{
    int ergebnis = 4;
    cout << "Jetzt liegen " << anzahlDerMuenzen << " Muenzen auf dem Tisch." << endl;
    while((ergebnis < 1) || (3 < ergebnis)){
        cout << "Wieviele moechten Sie nehmen? ";
        cin >> ergebnis;
        if((ergebnis < 1) || (3 < ergebnis))
            cout << "Sie duerfen nur 1, 2 oder 3 Muenzen ziehen!" << endl;
        if(ergebnis > anzahlDerMuenzen){
            cout << "So viele Muenzen liegen gar nicht mehr herum!" << endl;
            ergebnis = 4;
        }
    };

    return ergebnis;
};


int zugRechner(int anzahlDerMuenzen)
{
    int wunschZug = (anzahlDerMuenzen-1) % 4;
    if(wunschZug == 0)
        return 1;
    else
        return wunschZug;
};
