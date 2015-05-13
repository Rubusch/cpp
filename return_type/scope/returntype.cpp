// returntype.cpp
/*
  testing the scope of a returned variable
//*/


#include <iostream>

class SomeClass
{
public:
  SomeClass()
  {
    std::cout << "\t\tSomeClass() - ctor\n";
  }

  ~SomeClass()
  {
    std::cout << "\t\t~SomeClass() - dtor\n";
  }
};


class Foobar
{
public:
  SomeClass& getRef()
  {
    SomeClass local;
    std::cout << "\tlocal\t - addr\t = " << &local << "\n";
    // WARNING! Reference to local, finally only an "auto" variable will be initialized here
    return local;
  }

  SomeClass* getPtr()
  {
    SomeClass local;
    std::cout << "\tlocal\t - addr\t = " << &local << "\n";
    // WARNING! Bug to crash - the variable doesn't exist anymore outside this function!
    return &local;
  }

  SomeClass* getNew()
  {
    SomeClass* pLocal = new SomeClass;
    std::cout << "\tpLocal\t - addr\t = " << pLocal << "\n";
    return pLocal;
  }

  void func()
  {
    std::cout << "\tgetRef()\n";
    SomeClass object = getRef();
    std::cout << "\tobject\t - addr\t = " << &object << "\n\n";
    
    std::cout << "\tgetPtr()\n";
    SomeClass *pointer = getPtr();
    std::cout << "\tpointer\t - addr\t = " << pointer << "\n\n";

    std::cout << "\tgetNew()\n";
    pointer = getNew();
    std::cout << "\tpointer\t - addr\t = " << pointer << "\n\n";
    delete pointer; pointer = NULL;
  }
};


int main()
{
  using namespace std;
  Foobar fb;
  
  cout << "fb.getRef()\n";
  SomeClass object = fb.getRef();
  cout << "object\t\t - addr\t = " << &object << "\n\n";

  cout << "fb.getPtr()\n";
  SomeClass *pointer = fb.getPtr();
  cout << "pointer\t\t - addr\t = " << pointer << "\n\n";

  cout << "fb.getNew()\n";
  pointer = fb.getNew();
  cout << "pointer\t\t - addr\t = " << pointer << "\n\n";

  cout << "fb.func()\n";
  fb.func();

  delete pointer; pointer = NULL;

  cout << "READY.\n";
  return 0;
}
