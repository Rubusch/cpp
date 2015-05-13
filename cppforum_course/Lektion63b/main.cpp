// main.cpp
/*
  Bringt das Programm immer noch zum abstuerzen 
  -> Zuweisungsoperator ist noch nicht ueberladen.
//*/

#include <iostream>
using namespace std;

#include "vector.h"

int main()
{
    const int SIZE=100;
    Vector<bool> arr(SIZE);

    for(int i=0; i<SIZE; ++i){
        arr[i] = true;
    }
    
    for(int i=0; i<SIZE; ++i){
        for(int j=i; j<SIZE; j+=(i+1)){
            if(arr[j] == true)
                arr[j] = false;
            else
                arr[j] = true;
        };
    };

    cout << "Folgende Werte enthalten 0en: " << endl;
    for(int i=0; i<SIZE; ++i){
        if(arr[i] == false){
            cout << (i+1) << ". Wert" << endl;
        };
    };
};

