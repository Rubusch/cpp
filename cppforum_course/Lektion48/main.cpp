// main.cpp
/*
  Enthaelt die main() des Programms
//*/

#include <iostream>
using namespace std;
#include "swap.h"
#include "sort.h"


int main()
{
    int a=3;
    int b=5;
    int c=2;
    sort(&a,&b,&c);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
};

