// Prog.cpp
/*
  g++ (of the gcc package) uses signed char by default (?).
  This program will use the -funsigned-char option for the g++ compiler.
//*/

#include <iostream>
using namespace std;

int main()
{
    for(int zeichenNummer = 32; zeichenNummer < 128; ++zeichenNummer){
        char zeichen = zeichenNummer;
        cout << zeichenNummer << " :\t" << zeichen << '\t';
        if(zeichenNummer % 4 == 3)
            cout << endl;
    };

    return 0;
};


