// Prog.cpp
/*
  Fibonacci-Zahlen mit Rekursion, einfache Loesung.
//*/

#include <iostream>
using namespace std;

void fibonacci(int, int, int);

int main()
{
    int limit;
    int zahl=1;
    
    cout << "Wieviele Fibonacci-Zahlen sollen berechnet werden? ";
    cin >> limit;

    cout << 1 << endl;
    fibonacci(limit-1, 1, 0);
    
    return 0;
};


void fibonacci(int limit, int vorgaenger1, int vorgaenger2)
{
    int zahl = vorgaenger1 + vorgaenger2;
    
    --limit;
    if(0 == limit)
        return;
    else{
        cout << zahl << endl;
        fibonacci(limit, zahl, vorgaenger1);
    }
};
