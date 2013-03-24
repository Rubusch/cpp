// Prog.cpp
/*
  Primzahlenberechnung - Sieb des Eratosthenes.
  Anzahl der letzten Stellen der Primzahlen werden in ein 
  entsprechendes Array geschrieben.
//*/

#include <iostream>
using namespace std;

bool istPrimzahl(int);

int main()
{
    int limit=2;
    int idx=0;

    cout << "Bis zu welcher Zahl sollen die Primzahlen berechnet werden: ";
    cin >> limit;
    
    int arr[10];
    for(int i=0;i<10;++i) arr[i]=0;
    
    // cnt+=2 beschleunigt die Berechnung, mit einem anderen Aufbau lassen
    // sich die Schleifendurchlaeufe auch per <=sqrt(limit) verringern, hier nicht!
    for(int cnt=1; cnt<=limit; cnt+=2)
        if(istPrimzahl(cnt))
            ++arr[cnt%10];
    
    for(int i=0; i<10; ++i)
        cout << "xy" << i << " : " << arr[i] << endl;
    
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


