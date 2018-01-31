// Prog.cpp
/*
//*/

#include <iostream>
using namespace std;

class NimmSpiel
{
private:
    int anzahlDerMuenzen;
public:
    void zugRechner()
    {
        int wunschZug = anzahlDerMuenzen % 4;
        if(wunschZug == 0)
            anzahlDerMuenzen = anzahlDerMuenzen - 1;
        else
            anzahlDerMuenzen = anzahlDerMuenzen - wunschZug;
    };


    void zugMensch()
    {
        int ergebnis;
        cout << "Jetzt liegen " << anzahlDerMuenzen << " Muenzen auf dem Tisch." << endl;
        cout << "Wieviele moechten Sie nehmen? ";
        cin >> ergebnis;
        anzahlDerMuenzen = anzahlDerMuenzen - ergebnis;
    };


    bool gewonnen()
    {
        return anzahlDerMuenzen == 0;
    };


    void starteSpiel()
    {
        cout << "Mit wievielen Muenzen fangen wir an? ";
        cin >> anzahlDerMuenzen;
    };
};


int main()
{
    NimmSpiel spiel;
    spiel.starteSpiel();
    while(true){
        spiel.zugRechner();
        if(spiel.gewonnen()){
            cout << "Ich habe gewonnen!" << endl;
            return 0;
        };
        spiel.zugMensch();
        if(spiel.gewonnen()){
            cout << "Sie haben gewonnen!" << endl;
            return 0;
        };
    };

    return 0;
};
