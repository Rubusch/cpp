// Prog.cpp
/*
  endl vermeidet Verzoegerungen, da es den Zwischenspeicher automatisch flushed,
  da endl definiert ist als:

      cout << '\n' << flush;

  Ansonsten muss ein explizites "flush" gesetzt werden.
//*/

#include <iostream>
using namespace std;

int main()
{
    int i=1;
    while(i<=10){
        cout << "Schleifendurchlauf Nummer " << i << endl;
        ++i;
    };
};

