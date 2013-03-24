// Prog.cpp
/*
  Call by value - die Werte werden in der ausgelagerten Funktion 
  zwar vertauscht, aber das aufrufende Programm verwirft dies einfach.
  -> bei call-by-value bleiben keine Veraenderungen!!!
//*/

#include <iostream>
using namespace std;

void swap(int a, int b)
{
    int tmp=a;
    a=b;
    b=tmp;
};


int main()
{
    int a=1;
    int b=2;
    swap(a,b);
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    
    return 0;
};
