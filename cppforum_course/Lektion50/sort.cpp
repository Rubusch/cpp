// bubblesort.cpp
/*
//*/

#include <iostream>
using namespace std;
#include "sort.h"


Sort::Sort()
{
}


Sort::~Sort()
{
}


void Sort::swap(int *pa, int *pb)
{
    int tmp=*pa;
    *pa = *pb;
    *pb = tmp;
};


void Sort::bubbleSort(int *array, int size)
{
    int obergrenze = size - 1; 
    while(obergrenze > 0){
        int letzterAustausch=0;
        for(int pos = 0; pos < obergrenze; ++pos){
            if(array[pos] > array[pos+1]){
                swap(&array[pos], &array[pos+1]);
                letzterAustausch = pos;
            };
        };
        obergrenze = letzterAustausch;
    };
};


void Sort::straightSelectionSort(int *array, int size)
{
    for(int arrayAnfang = 0; arrayAnfang < size - 1; ++arrayAnfang){
        // array Anfang laeuft von 0 bis eins vor Ende des Arrays

        // Suchen des kleinsten Wertes
        int minPos = arrayAnfang;
        
        int minWert = array[arrayAnfang];
        for(int suchPos = arrayAnfang + 1; suchPos < size; ++suchPos){
            if(array[suchPos] < array[minPos]){
                minPos = suchPos;
                minWert = array[suchPos];
            };
        };
        // Und austauchen
        swap(&array[arrayAnfang], &array[minPos]);
    };
};


void test()
{
    const int SIZE=10;
    int array[SIZE];
    Sort s;
    
    // array mit Zufallszahlen kleiner als SIZE fuellen
    for(int i=0; i<SIZE; ++i)
        array[i] = rand()%SIZE;

    // alle Zahlen in einer Zeile ausgeben
    for(int i=0; i<SIZE; ++i)
        cout << array[i] << ' ';
    
    // sortieren
    s.bubbleSort(array, SIZE);
    cout << " ->  ";

    // nach dem sortieren ausgeben
    for(int i=0; i<SIZE; ++i)
        cout << array[i] << ' ';
    
    // zum pruefen des Sortier-Algorithmus: ist eine Zahl groesser
    // als der darauffolgende Wert? (dann hat unser Algorithmus 
    // fehlerhaft gearbeitet.
    for(int i=0; i<SIZE-1; ++i){
        if(array[i] > array[i+1]){
            cout << "Fehler!" << endl;
            
            // wartet auf Tastendruck
            cin.get();    
        };
    };
    cout << endl;
};


int main()
{
    for(int i=0; i<10; ++i)
        test();
};
