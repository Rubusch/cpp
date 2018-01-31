// beta.cpp
/*
//*/

#include "beta.h"

B::B()
{
    cout << "Constructor B" << endl;
};


void B::doSomething()
{
    cout << "B::doSomething()" << endl;
    for(int i=0; i<10; ++i)
        cout << "blah" << endl;
};
