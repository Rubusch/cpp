// main.cpp
/*
  Die Klasse string
//*/

#include <iostream>
#include <string>
using namespace std;

void swap(string *pa, string *pb)
{
    string tmp=*pa;
    *pa=*pb;
    *pb=tmp;
};


void bubbleSort(string *array, int size)
{
    for(int obergrenze = size -1; obergrenze > 0; --obergrenze){
        for(int pos=0; pos < obergrenze; ++pos){
            if(array[pos] > array[pos+1])
                swap(&array[pos], &array[pos+1]);
        };
    };
};


int main()
{
    int i;
    const int ANZAHL_NAMEN = 5;
    string namen[ANZAHL_NAMEN];
    cout << "Bitte geben Sie " << ANZAHL_NAMEN << " Namen ein!" << endl;
    for(i=0; i < ANZAHL_NAMEN; ++i)
        cin >> namen[i];
    bubbleSort(namen, ANZAHL_NAMEN);
    cout << "Die Namen sortiert:" << endl;
    for(i=0; i < ANZAHL_NAMEN; ++i)
        cout << namen[i] << endl;
    
    return 0;
};
