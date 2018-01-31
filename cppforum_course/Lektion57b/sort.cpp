// bubblesort.cpp
/*
//*/

#include <iostream>
using namespace std;
#include "sort.h"


Sort::Sort()
{
};


Sort::~Sort()
{
};


template<class T>
void Sort::swap(T *pa, T *pb)
{
    T tmp=*pa;
    *pa = *pb;
    *pb = tmp;
};


template<class T>
void Sort::bubbleSort(T *array, int size)
{
    int obergrenze = size - 1;
    while(obergrenze > 0){
        int letzterAustausch=0;
        for(int pos = 0; pos < obergrenze; ++pos){
            if(array[pos] > array[pos+1]){
                Sort::swap(&array[pos], &array[pos+1]);
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
        Sort::swap(&array[arrayAnfang], &array[minPos]);
    };
};


void Sort::straightInsertionSort(int *array, int size)
{
    for(int i = 0; i < size; ++i){
        for(int j=i; j >= 0; --j){
            if(array[j-1] > array[j])
                Sort::swap(&array[j-1], &array[j]);
            else
                break;
        };
    };
};


void Sort::shellSort(int *array, int size)
{
    int step;
    for(step=1; step<size; step = 3*step+1) ;

    do
    {
        step = (step-1)/3;

        for(int start = 0; start < step; ++start){
            for(int i = start + 1; i < size; i += step){
                for(int j = i - 1; (j >= 0) && (j+step < size); j -= step){
                    if(array[j] > array[j + step])
                        swap(&array[j], &array[j+step]);
                    else
                        break;
                };
            };
        };
    }while(step>0);
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
    s.shellSort(array, SIZE);
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
