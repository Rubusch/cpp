// Prog.cpp
/*
  new und delete fuer Arrays
//*/

#include <iostream>
using namespace std;

int main()
{
    int SIZE = 5;
    int i;

    // Array mit 5 int Werten anlegen
    int *pi=new int[SIZE];

    // fuellen mit 0,2,4,6,8
    for(int i=0; i<SIZE; ++i)
        pi[i] = 2*i;

    // Ausgabe von 0,2,4,6,8
    for(int i=0; i<SIZE; ++i)
        cout << pi[i] << endl;

    // Array wieder loeschen mit delete
    delete[] pi;
};

