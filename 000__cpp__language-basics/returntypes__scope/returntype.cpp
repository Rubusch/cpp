// returntype.cpp
/*
  testing the scope of a returned variable
//*/


#include <iostream>

using namespace std;


class SomeClass
{
public:
  SomeClass() = default;
  ~SomeClass() = default;
};


class Foobar
{
public:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-local-addr"
  SomeClass &getRef()
  {
    SomeClass local;
    cout << "\tlocal\t - addr\t = " << &local << "\n";
    // WARNING! Reference to local, finally only an "auto" variable will be
    // initialized here NEVER DO THIS!
    return local;
  }

  SomeClass *getPtr()
  {
    SomeClass local;
    cout << "\tlocal\t - addr\t = " << &local << "\n";
    // WARNING! Bug to crash - the variable doesn't exist anymore outside this
    // function! NEVER DO THIS!
    return &local;
  }
#pragma GCC diagnostic pop
  SomeClass *getNew()
  {
    SomeClass *pLocal = new SomeClass;
    cout << "\tpLocal\t - addr\t = " << pLocal << "\n";
    return pLocal;
  }

  void func()
  {
    cout << "\tgetRef()\n";
    SomeClass object = getRef();
    cout << "\tobject\t - addr\t = " << &object << "\n\n";

    cout << "\tgetPtr()\n";
    SomeClass *pointer = getPtr();
    cout << "\tpointer\t - addr\t = " << pointer << "\n\n";

    cout << "\tgetNew()\n";
    pointer = getNew();
    cout << "\tpointer\t - addr\t = " << pointer << "\n\n";
    delete pointer;
    pointer = NULL;
  }
};


int main()
{
  Foobar fb;
  SomeClass *pointer = nullptr;

  cout << "fb.getRef()\n";
  SomeClass object = fb.getRef();
  cout << "object\t\t - addr\t = " << &object << "\n\n";

  cout << "fb.getPtr()\n";
  pointer = fb.getPtr();
  cout << "pointer\t\t - addr\t = " << pointer << "\n\n";

  cout << "fb.getNew()\n";
  pointer = fb.getNew();
  cout << "pointer\t\t - addr\t = " << pointer << "\n\n";

  cout << "fb.func()\n";
  fb.func();

  delete pointer;
  pointer = NULL;

  cout << "READY.\n";
  return 0;
}
