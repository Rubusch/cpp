// main.cpp
/*
//*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    cout << "speichern..." << endl;
    
    ofstream out("witz.txt");
    out << "Es kommt ein Mann zum Baecker und..." << endl;
    out << "Da fragt der Baecker..." << endl;
    out << "Der Mann antwortet: Nein.." << endl;
    {        
        cout << endl << "...laden, als Stream:" << endl;
        ifstream in("witz.txt");
        while(!in.eof()){
            char ch;
            in >> ch;
            cout << ch;
        };
    };
    {
        cout << endl << "...laden, Zeichen fuer Zeichen:" << endl;
        ifstream in("witz.txt");
        while(!in.eof()){
            char ch;
            ch = in.get();
            cout << ch;
        };
    };
    {
        cout << endl;
        cout << endl << "...laden, optimal ohne zusaetzliches Zeichen:" << endl;
        string sz;
        ifstream in("witz.txt");
        while(!in.eof()){
            sz += in.get();
        };
        sz = sz.erase(sz.length()-1);
        cout << sz << endl;
    };
    
    return 0;
};
