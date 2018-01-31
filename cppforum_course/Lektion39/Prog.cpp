// Prog.cpp
/*
  new und delete und Situationen in denen delete nicht moeglich ist.
//*/

#include <iostream>
using namespace std;

int main()
{
    // Speicherplatz fuer einen int anlegen
    int *pi=new int;

    // 5 reinschreiben
    *pi=5;

    // Ausgabe 5
    cout << *pi << endl;

    // Speicherplatz loeschen
    delete pi;

    // nochmal Speicherplatz anlegen
    pi=new int;

    // eine normale int Variable
    int i=6;

    // Ausgabe: irgend eine Zahl...
    cout << *pi << endl;

    // pi ist Adresse von i
    pi=&i;

    // Jetzt ist die Adresse des int auf dem heap verloren. Er kann
    // nicht mehr mit delete freigegeben werden!!!

    // Ausgabe 6
    cout << *pi << endl;

    // Fehler!!! Die Variable i kann so nicht geloescht werden!
    delete pi;
};
