// Main.cpp
/*
  Pointer & References

  There are only three different ways setting a pointer:

  Definition:
      int* pVar = &var;
      // pVar points to var

  Declaration and Initialisation (later):
      int* pVar=NULL;
      pVar = &var;
      // same as above
  or
      int* pVar=NULL;
      // pVar here needs allocation 'pVar = new int;'
      *pVar = var;
      // then pVar needs 'delete pVar;'

  here the value is copied into some space the pointer
  points to, thus the pointer first needs to have 'valid'
  memory e.g. by dynamic allocation
//*/

#include <iostream>
#include <string>

using namespace std;


void display(string szName, string szCommand, int *p)
{
  cout << szCommand << "   :\t" << szName << " = " << p << ",\t*" << szName
       << " = " << *p << ",\t&" << szName << " = " << &p << endl;
};


int main()
{
  cout << " - Pointer Demo - " << endl;
  cout << endl;

  cout << "Declaration of Variables:" << endl;

  int var = 777;
  cout << "var = 777   :\t\tvar = " << var << ",\t&var = " << &var << endl;
  cout << endl;

  cout << "Deklaration and initialisation of a pointer:" << endl;
  {
    int *pVar1 = &var;
    display("pVar1", "int* pVar1 = &var", pVar1);
    cout << endl;
  };

  {
    //        int* pVar2 = var;
    cout << "int* pVar2 = var, Invalid conversion from \'int\' to \'int*\'"
         << endl;
    cout << endl;
  };


  cout << "Initialisation of an already declared pointer:" << endl;
  {
    int *pVar3 = NULL;
    //        pVar3 = var;
    cout << "pVar3 = var, Invalid conversion from \'int\' to \'int*\'" << endl;
    cout << endl;
  };
  {
    int *pVar4 = NULL;
    pVar4 = &var;
    display("pVar4", "pVar4 = &var", pVar4);
    cout << endl;
  };
  {
    int *pVar5 = NULL;
    pVar5 = new int; // ATTENTION! *pVar5 until now still had no memory!
    *pVar5 = var;
    display("pVar5", "*pVar5 = var", pVar5);
    delete pVar5; // don't forget to free the memory
    cout << endl;
    /* without allocation of *pVar5 it even may work by chance,
       or more likely it may throw a segmentation fault */
  };
  {
    int *pVar6 = NULL;
    //        *pVar6 = &var;
    cout << "*pVar6 = &var, Invalid conversion from \'int*\' to \'int\'"
         << endl;
    cout << endl;
  };
  {
    int *pVar7 = NULL;
    //        &pVar7 = var;
    cout << "&pVar7 = var, Invalid lvalue in assignment" << endl;
    cout << endl;
  };
  {
    int *pVar8 = NULL;
    //        &pVar8 = &var;
    cout << "&pVar8 = &var, Invalid lvalue in assignment" << endl;
    cout << endl;
  };

  return 0;
};
