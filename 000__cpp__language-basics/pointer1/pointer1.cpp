// Main.cpp
/*
  Pointer & References

  There are only three different ways setting a pointer:

  Definition:
      int* pVar = &var;
      // pVar points to var

  Declaration and Initialisation (later):
      int* pVar=nullptr;
      pVar = &var;
      // same as above
  or
      int* pVar=nullptr;
      // pVar here needs allocation 'pVar = new int;'
      *pVar = var;
      // then pVar needs 'delete pVar;'

  here the value is copied into some space the pointer points to, thus
  the pointer first needs to have 'valid' memory e.g. by dynamic
  allocation
//*/

#include <iostream>
#include <string>

using namespace std;


void display(string szName, string szCommand, int *p)
{
  cout << szCommand << ":\t" << szName << " = " << p << ";\t*" << szName
       << " = " << *p << ";\t&" << szName << " = " << &p << endl;
};


int main()
{
  cout << " - Pointer Demo - " << endl;
  cout << endl;

  cout << "Declaration of Variables:" << endl;

  cout << "int var = 777;" << endl;
  int var = 777;
  cout << "content:\t\tvar = " << var << ";\t&var = " << &var << ";" << endl; // TODO xxx
  cout << endl;

  cout << "Declaration and initialisation of a pointer:" << endl;
  {
    int *pVar1 = &var;
    display("pVar1", "content", pVar1);
  };

  {
    cout << "int* pVar2 = var;\t// Invalid conversion from \'int\' to \'int*\'"
         << endl;
//  int* pVar2 = var; // FAILS!
    cout << endl;
  };


  cout << "Initialisation of an already declared pointer:" << endl;
  {
	cout << "int *pVar3 = NULL;" << endl;
    int *pVar3 = NULL;
//  pVar3 = var; // FAILS!
    cout << "pVar3 = var;\t// Invalid conversion from \'int\' to \'int*\'" << endl;
    cout << endl;
  };
  {
	cout << "int *pVar4 = NULL;" << endl;
    int *pVar4 = NULL;
	cout << "pVar4 = &var;" << endl;
    pVar4 = &var;
    display("pVar4", "content", pVar4);
    cout << endl;
  };
  {
    cout << "int *pVar5 = NULL;" << endl;
	int *pVar5 = NULL;
	cout << "pVar5 = new int;" << endl;
    pVar5 = new int; // ATTENTION! *pVar5 until now still had no memory!
    cout << "*pVar5 = var;" << endl;
	*pVar5 = var;
    display("pVar5", "content", pVar5);
    delete pVar5; // don't forget to free the memory
    cout << endl;
    /* without allocation of *pVar5 it even may work by chance,
       or more likely it may throw a segmentation fault */
  };
  {
	cout << "int *pVar6 = NULL;" << endl;
    int *pVar6 = NULL;
    cout << "*pVar6 = &var;\t// Invalid conversion from \'int*\' to \'int\'"
         << endl;
//  *pVar6 = &var; // FAILS!
    cout << endl;
  };
  {
	cout << "int *pVar7 = NULL;" << endl;
    int *pVar7 = NULL;
    cout << "&pVar7 = var;\t// Invalid lvalue in assignment" << endl;
//  &pVar7 = var; // FAILS!
	cout << endl;
  };
  {
	cout << "int *pVar8 = NULL;" << endl;
    int *pVar8 = NULL;
    cout << "&pVar8 = &var;\t// Invalid lvalue in assignment" << endl;
//  &pVar8 = &var; // FAILS!
    cout << endl;
  };

  cout << "READY." << endl;
  return 0;
};
