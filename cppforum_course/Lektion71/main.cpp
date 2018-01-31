// main.cpp
/*
  Nichtfunktionierende Version - sh. naechstes Kapitel
//*/

#include <iostream>
#include <string>
using namespace std;

#include "SortedArray.h"
#include "DefaultComparator.h"
#include "Dictionary.h"

int main()
{
    Dictionary< string, int > d;

    d.insert("eins", 1);
    d.insert("zwei", 2);
    d.insert("drei", 3);

    for(int i=0; i<d.getSize(); ++i)
        cout << d[i].getKey() << ' ' << d[i].getValue() << endl;

    return 0;
};
