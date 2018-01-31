// Prog.cpp
/*
  Overflow, Underflow
  short, long und int sind by default signed.
  signed oder unsigned char haengt von den Compilereinstellungen ab.
//*/

#include <limits>
#include <iostream>
using namespace std;

int main()
{
    cout << "Underflow: " << endl;
    cout << "INT_MIN + INT_MIN = ("
         << INT_MIN << ") + (" << INT_MIN << ") = "
         << INT_MIN + INT_MIN << endl;
    cout << endl;

    cout << "Korrekte Berechnung: " << endl;
    cout << "INT_MAX + INT_MIN = ("
         << INT_MAX << ") + (" << INT_MIN << ") = "
         << INT_MAX + INT_MIN << endl;
    cout << endl;

    cout << "Overflow: " << endl;
    cout << "INT_MAX + INT_MAX = ("
         << INT_MAX << ") + (" << INT_MAX << ") = "
         << INT_MAX + INT_MAX << endl;
    cout << endl;

    return 0;
};

