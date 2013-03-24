// main.cpp
/*
//*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include "vector.h"
#include "set.h"

int main()
{
    srand(time(0));
    int gewonnen = 0;
    while(gewonnen < 3){
        // Zufallszahl zwischen 0 und 99
        int ziel = rand() % 100;
        
        int geraten;
        for(int versuch = 1; versuch <= 7; ++versuch){
            cout << "Zahl eingeben: ";
            cin >> geraten;
            if(ziel < geraten)
                cout << "kleiner" << endl;
            else
                cout << "nicht kleiner" << endl;
        };
        cout << "Wie heisst die Zahl? " << endl;
        cin >> geraten;
        if(geraten == ziel){
            cout << "Sie haben es geschafft!" << endl;
            ++gewonnen;
        }else{
            cout << "Nein! Die Zahl war " << ziel << endl;
            gewonnen = 0;
        };
    };
    cout << "Sie haben drei mal hintereinander gewonnen." << endl;
    cout << "Die naechste Lektion ist jetzt gut vorbereitet." << endl;
};


