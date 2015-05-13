// Prog.cpp
/*
  Zeigervariablen als Uebergabeparameter - pass by reference
  Eine ausgelagerte Funktion vertauscht die Adressen zweier Werte.
  Hier werden die Werte auch in der aufrufenden Funktion vertauscht.
  Funktionen ausserhalb koennen also mit Zeigern auch Werte dauerhaft 
  veraendern.
//*/

#include <iostream>
using namespace std;

void swap(int *pa, int *pb)
{
    // tmp ist "Inhalt von a"
    int tmp=*pa;

    // "Inhalt von a" ist "Inhalt von b"
    *pa=*pb;
    
    // "Inhalt von b" ist tmp
    *pb=tmp;
};


int main()
{
    int a=1;
    int b=2;
    swap(&a, &b);
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    
    return 0;
};

    
