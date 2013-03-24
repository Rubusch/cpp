// Prog.cpp
/*
  Einige Zeichenfunktionen fuer char und ANSI Zeichensatz.
  char xy ist das Character-Gegenstueck der jeweiligen int Zahl.
  Man kann genausogut mit Zahlen rechnen, wie mit char Werten.
//*/

#include <iostream>
using namespace std;

bool isdigit(char);
bool isalpha(char);
bool islower(char);
bool isupper(char);
char tolower(char);
char toupper(char);

int main()
{
    char zeichen;
    cout << "Geben Sie ein einzelnes Zeichen ein: ";
    cin >> zeichen;
    cout << '\'' << zeichen << '\'' << " wurde eingelesen." << endl;

    cout << "Zahl:\t\t\t" << (isdigit(zeichen)?"ja":"nein") << endl;
    cout << "Buchstabe:\t\t" << (isalpha(zeichen)?"ja":"nein") << endl;
    if(islower(zeichen)){
        cout << '\'' << zeichen << '\'' << " ist ein Kleinbuchstabe," << endl;
        cout << "in gross:\t\t" << toupper(zeichen) << endl;
    };

    if(isupper(zeichen)){
        cout << '\'' << zeichen << '\'' << " ist ein Grossbuchstabe." << endl;
        cout << "in klein:\t\t" << tolower(zeichen) << endl;
    };

    return 0;
};


bool isdigit(char ch)
{
    return '0'<=ch && ch<='9';
};


bool isalpha(char ch)
{
    return islower(ch) || isupper(ch);
};


bool islower(char ch)
{
    return 'a'<=ch && ch<='z';
};


bool isupper(char ch)
{
    return 'A'<=ch && ch<='Z';
};


char tolower(char ch)
{
    return ch + ('a'-'A');
};


char toupper(char ch)
{
    return ch - ('a'-'A');
};

