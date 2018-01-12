// Main.cpp
/*

  Pointer & References

  There are only three different ways setting a pointer:

  Definition (directly):
      int* pVar = &var;

  Declaration and Initialisation (later):
      int* pVar;
      pVar = &var;
  (which is basically the same as above)

  or
      int* pVar;
      *pVar = var;
  (which just inits by the value)
//*/

#include <iostream>
#include <string>
using namespace std;

void display(string szName, string szCommand, int *p)
{
    cout << szCommand
         << "   :\t" << szName << " = " << p
         << ",\t*" << szName << " = " << *p
         << ",\t&" << szName << " = " << &p
         << endl;
};


int main()
{
    cout << " - Pointer Demo - " << endl;
    cout << endl;

    cout << "Declaration of Variables:" << endl;

    int var = 777;
    cout << "var = 777   :\t\tvar = " << var
         << ",\t&var = " << &var << endl;
    cout << endl;



    cout << "Deklaration and initialisation of a pointer:" << endl;
    {
        int* pVar1 = &var;
        display("pVar1", "int* pVar1 = &var", pVar1);
        cout << endl;
    };

    {
//        int* pVar2 = var;
        cout << "int* pVar2 = var, Invalid conversion from \'int\' to \'int*\'" << endl;
        cout << endl;
    };


    cout << "Initialisation of an already declared pointer:" << endl;
    {
        int* pVar3;
//        pVar3 = var;
        cout << "pVar3 = var, Invalid conversion from \'int\' to \'int*\'" << endl;
        cout << endl;
    };
    {
        int* pVar4;
        pVar4 = &var;
        display("pVar4", "pVar4 = &var", pVar4);
        cout << endl;
    };
    {
        int* pVar5;
        *pVar5 = var;
        display("pVar5", "*pVar5 = var", pVar5);
        cout << endl;
    };
    {
        int* pVar6;
//        *pVar6 = &var;
        cout << "*pVar6 = &var, Invalid conversion from \'int*\' to \'int\'" << endl;
        cout << endl;
    };
    {
        int* pVar7;
//        &pVar7 = var;
        cout << "&pVar7 = var, Invalid lvalue in assignment" << endl;
        cout << endl;
    };
    {
        int* pVar8;
//        &pVar8 = &var;
        cout << "&pVar8 = &var, Invalid lvalue in assignment" << endl;
        cout << endl;
    };

    return 0;
};
