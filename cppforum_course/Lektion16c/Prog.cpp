// Prog.cpp
/*
  Fibonacci-Zahlen mit Rekursion, optimale Loesung.
//*/

#include <iostream>
using namespace std;

int fibRek(int);

int main()
{
    int limit;
    int zahl=1;
    
    cout << "Wieviele Fibonacci-Zahlen sollen berechnet werden? ";
    cin >> limit;

    for(int i=1; i<limit; ++i)
        cout << fibRek(i) << endl;
    
    return 0;
};


int fibRek(int n)
{
    if(n == 1)
        return 1;
    else if(n == 2)
        return 1;
    else
        return fibRek(n-1) + fibRek(n-2);
};
