// main.cpp
/*
//*/

#include <iostream>
#include <string>
using namespace std;

#include "vector.h"
#include "SortedArray.h"

int main()
{
    SortedArray<string> s;
    s.insert("Hans");
    s.insert("Klaus");
    s.insert("ich");
    s.insert("Fritz");
    s.insert("Anna");
    cout << endl;
    for(int i=0; i<s.getSize(); ++i)
        cout << i << ". " << s[i] << endl;

    cout << endl;
    cout << "Hans: " << s.findIndex("Hans") << endl;
    cout << "Klaus: " << s.findIndex("Klaus") << endl;
    cout << "Fritz: " << s.findIndex("Fritz") << endl;
    cout << "ich: " << s.findIndex("ich") << endl;
    cout << "Anna: " << s.findIndex("Anna") << endl;
    cout << "Sepp: " << s.findIndex("Sepp") << endl;


    return 0;
};
