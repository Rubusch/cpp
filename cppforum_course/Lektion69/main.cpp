// main.cpp
/*
  Nutzung von Default Template Argumenten und Nutzung von Templates in Templatedeklarationen.

  Template in Template immer ein Whitespace zwischen den '>' machen, sonst isses >>
//*/

#include <iostream>
#include <string>
using namespace std;

#include "SortedArray.h"
#include "DefaultComparator.h"

int main()
{
    const int MAX = 100;

// Beides funktioniert nun!
//    SortedArray< int, DefaultComparator<int> > s;
    SortedArray< int > s;

    for(int waerter = 1; waerter <= MAX; ++waerter){
        for(int tuer=waerter; tuer <= MAX; tuer += waerter){
            if(s.has(tuer))
                s.remove(tuer);
            else
                s.insert(tuer);
        };
    };

    for(int i=0; i<s.getSize(); ++i)
        cout << s[i] << endl;

    return 0;
};
