// Prog.cpp
/*
  Einfuehrung in structs - erstellen und zugreifen.
//*/

#include <iostream>
using namespace std;

struct Uhrzeit
{
    int stunde;
    int minute;
};


int main()
{
    // neuer Typ kann wie int, float... fuer Variablen verwendet werden
    Uhrzeit arbeitsBeginn;
    Uhrzeit arbeitsEnde;

    // Attribute werden ueber '.' zwischen Variablenname 
    // und Attributename angesprochen
    arbeitsBeginn.stunde = 8;
    arbeitsBeginn.minute = 30;
    
    arbeitsEnde.stunde = 18;
    arbeitsEnde.minute = 15;
    
    // Formatierungen sind dem compiler egal, daher kann ein Befehl auch
    // ueber viele Zeilen gehen!
    int arbeitsMinuten = 60 * (arbeitsEnde.stunde - arbeitsBeginn.stunde)
        + arbeitsEnde.minute - arbeitsBeginn.minute;
    
    cout << arbeitsMinuten << " Minuten" << endl;
};
