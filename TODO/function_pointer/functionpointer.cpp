// functionpointer.cpp
/*
  Function pointer example. Best practices around function pointers,
  which may be rather C style than C++.

  (idea taken from Alexandrescu, 2001)


  The usages of an index into a vector and dereferencing a function pointer is most times
  more efficient than processing lots of if-then-else statements.

  (More Effective C++ / 31 / Meyers)
//*/


#include <iostream>


void function_A()
{
  std::cout << "\tfunction_A()\n";
}

void function_B()
{
  std::cout << "\tfunction_B()\n";
}


int main()
{
  using namespace std;

  cout << "define a function pointer and init it with the address of function_A()\n";
  void (*pFunc)() = &function_A;

  cout << "call functions directly\n";
  function_A();
  function_B();
  cout << endl;

  cout << "call functions via function pointer\n";
  (*pFunc)();
  cout << endl;

  cout << "create pCopy, a copy of function pointer\n";
  void (*pCopy)() = pFunc;
  cout << endl;

  cout << "call pCopy -> function_A()\n";
  (*pCopy)();
  cout << endl;

  cout << "change pFunc to point to function_B()\n";
  pFunc = &function_B;
  cout << endl;

  cout << "call pFunc -> function_B\n";
  (*pFunc)();
  cout << endl;

  cout << "call pCopy again, after we changed pFunc, still points to function_A()\n";
  (*pCopy)();
  cout << endl;


  cout << "READY.\n";
  return 0;
}
