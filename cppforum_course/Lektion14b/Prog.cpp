// Prog.cpp
/*
  Primzahlenberechnung - Sieb des Eratosthenes.
//*/

#include <iostream>
using namespace std;

bool istPrimzahl(int);

int main()
{
    int limit=2;

    cout << "Bis zu welcher Zahl sollen die Primzahlen berechnet werden: ";
    cin >> limit;
    
    for(int cnt=2; cnt<=limit; ++cnt){
        if(istPrimzahl(cnt))         
            cout << cnt << endl;
    }

    return 0;
};

bool istPrimzahl(int zahl)
{
    bool ist=true;
    
    if(zahl == 0) return false;
    if(zahl == 1) return true;
    
    for(int cnt = zahl-1; cnt > 1; --cnt){
        if(zahl%cnt == 0){
            ist = false;
            break;
        }
    }

    return ist;
};


