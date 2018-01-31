// main.cpp
/*
  Vererbung an Hand von Vogelgetier
//*/

#include <iostream>
using namespace std;

class Vogel
{
public:
    void fliege()
    {
        cout << "Ich fliege durch die Luft: Flap Flap Flap\n";
    };
};


class Singvogel:public Vogel
{
};


class Amsel:public Singvogel
{
};


class Sperling:public Singvogel
{
};


class Pinguin:public Vogel
{
public:
    void fliege()
    {
        cout << "Ich fliege durch das Wasser: Blub Blub Blub\n";
    };
};


int main()
{
    Vogel v;
    Singvogel s;
    v.fliege();
    s.fliege();

    Amsel am;
    Sperling sp;
    Pinguin pi;
    am.fliege();
    sp.fliege();
    pi.fliege();

    return 0;
};
