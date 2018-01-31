// bubblesort.cpp
/*
//*/

#include <iostream>
using namespace std;

void swap(int *pa, int *pb)
{
    int tmp=*pa;
    *pa = *pb;
    *pb = tmp;
};


void bubbleSort(int *array, int size)
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


void test()
{
    const int SIZE=10;
    int array[SIZE];

    // array mit Zufallszahlen kleiner als SIZE fuellen
    for(int i=0; i<SIZE; ++i)
        array[i] = rand()%SIZE;

    // alle Zahlen in einer Zeile ausgeben
    for(int i=0; i<SIZE; ++i)
        cout << array[i] << ' ';

    // sortieren
    bubbleSort(array, SIZE);

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
    for(int i=0; i<1000000; ++i)
        test();
};




