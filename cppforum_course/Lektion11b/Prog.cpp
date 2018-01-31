// Prog.cpp
/*
  Schaltjahr: nur durch 4 teilbar und 400 teilbar - einfache Loesung.
//*/

#include <iostream>
using namespace std;

bool istSchaltjahr(int jahr)
{
    if(jahr < 0)
        return false;

    if(jahr%4==0){
        cout << "Durch 4 teilbar." << endl;

        if(jahr%100 == 0){
            cout << "Durch 100 teilbar." << endl;
            if(jahr%400 == 0){
                cout << "Durch 400 teilbar." << endl;
                return true;
            }else{
                cout << "Nicht durch 400 teilbar." << endl;
                return false;
            }
        }else{
            cout << "Nicht durch 100 teilbar aber durch 4." << endl;
            return true;
        }
    }else{
        cout << "Nicht durch 4 teilbar." << endl;
        return false;
    }
};


int main()
{
    int jahr=0;

    cout << "Geben Sie eine Jahreszahl ein: ";
    cin >> jahr;
    if(istSchaltjahr(jahr))
        cout << "Das ist ein Schaltjahr." << endl;
    else
        cout << "Kein Schaltjahr." << endl;

    return 0;
};

