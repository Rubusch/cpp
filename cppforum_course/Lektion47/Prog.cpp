// Prog.cpp
/*
  Euklidische Algorithmus - iterative Loesung
  Der Euklidische Algorithmus ist ein Algorithmus zum auffinden des
  groessten gemeinsamen Teilers.
//*/

#include <iostream>
using namespace std;

int ggt(int, int);
void swap(int *a, int *b);

int main()
{
    int a=0, b=0;

    cout << "Geben Sie die erste Zahl ein: ";
    cin >> a;
    cout << "Geben Sie die zweite Zahl ein: ";
    cin >> b;
    
    cout << "Der groesste gemeinsame Teiler ist: " << ggt(a,b) << endl;

    return 0;
};


int ggt(int a, int b)
{
    int tmp=0;
    
    if(a>b) swap(a,b);
        
    while(b!=0){
        tmp=a;
        a=b;
        b=tmp%b;
    }
    return a;
};


void swap(int *a, int *b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
};



