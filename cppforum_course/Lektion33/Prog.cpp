// Prog.cpp
/*
  Dreieckstausch
//*/

#include <iostream>
using namespace std;

int main()
{
    int a=1;
    int b=2;
    {
        int tmp=a;
        a=b;
        b=tmp;
    };
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    return 0;
};
