// Main.cpp
/*
  Three ways of passing parameters in functions
  
  pass by value
     The original value won't be modified. Works with a copy 
     of the content of the original value.

  pass by pointer
     The original value can be changed. The passed value can 
     also be NULL. 

  pass by reference - const reference
     This works with the original value, but is made const 
     to not allow any modification to the original value. The 
     "const" is quite convenient in many cases. 
//*/

#include <iostream>
#include <string>
using namespace std;

void passByValue(int v, int p)
{
    cout << "Function: ++v; ++p;\t\t";
    ++v;
    ++p;
    cout << "v = " << v << ", p = " << p << endl;
};


void passByReference_Pointer(int *v, int *p)
{
    cout << "Function: ++*v; ++*p;\t\t";
    ++*v;
    ++*p;
    cout << "*v = " << *v << ", *p = " << *p << endl;
};


void passByReference_Reference(const int &v, const int &p)
{
    cout << "Function: ++v; ++p; doesn't work due to const! "
         << "(v + 1) = " << (v + 1) << ", (p + 1) = " << (p + 1) << endl;
};


int main()
{
    int var = 7;
    int dummy = 8;
    int* pVar = &dummy;

    cout << "Main: var = " << var << ", *pVar = " << *pVar << endl << endl;
    
    cout << "pass by value" << endl;
    passByValue(var, *pVar);
    cout << "Main: var = " << var << ", *pVar = " << *pVar << endl << endl;
    
    cout << "pass by reference - address" << endl;
    passByReference_Pointer(&var, pVar);
    cout << "Main: var = " << var << ", *pVar = " << *pVar << endl << endl;
    
    cout << "pass by reference - const reference" << endl;
    passByReference_Reference(var, *pVar);
    cout << "Main: var = " << var << ", *pVar = " << *pVar << endl << endl;    

    return 0;
};
