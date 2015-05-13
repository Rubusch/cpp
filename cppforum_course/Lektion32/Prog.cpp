// Prog.cpp
/*
  Zeiger
//*/

#include <iostream>
using namespace std;

int main()
{
    // a ist 5
    int a=5;
    
    // Ausgabe 5
    cout << a << endl;
    
    // Zeiger pa ist Adresse von a
    int *pa=&a;

    // Inhalt von pa ist 6
    *pa=6;
    
    // Ausgabe 6
    cout << a << endl;
    
    // a ist 7
    a=7;

    // Ausgabe 7
    cout << *pa << endl;
    
    // b ist 8
    int b=8;
    
    // Zeiger pb ist pa, pb zeigt jetzt auch auf a
    int *pb=pa;
    
    // Ausgabe 7
    cout << *pb << endl;
    
    // Zeiger Zeiger ppa = Adresse von pa
    int **ppa=&pa;
    
    // Ausgabe 7
    cout << **ppa << endl;
    
    // Inhalt von ppa ist Adresse von pb
    ppa=&pb;
    
    // Ausgabe 7
    cout << **ppa << endl;
    
    // pb ist Adresse von b
    pb=&b;
    
    // Ausgabe 8
    cout << **ppa << endl;
    
    return 0;
};
