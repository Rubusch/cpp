// passbywhat.cpp
/*
  demonstrates
  - pass-by-value
  - pass-by-reference (pass-by-reference using a reference)
  - pass-by-pointer (pass-by-reference using a pointer)
//*/


#include <iostream>

template<class T>
class Acceptor
{
private:
  const T* pVal;

public:
  // Ctor - init in headline!
  Acceptor()
  :pVal(NULL)
  {}

  // Cpy Ctor
  // ...

  // Dtor
  ~Acceptor()
  {
    // when pVal is allocated within the class its destruction should happen here!
    // Handle the delete of the allocated memory where it has been allocated, too,
    // or distinguish here between allocated pVal and static pVal (bad style) - a
    // solution using enum/templates might be possible (Alexandrescu)
  }

  // ops: assignment, index, new, delete, etc
  // ...


  /*
    F U N C T I O N S
  //*/


  /*
    "val" is a stack variable, elements would be accessed by using '.'

    1. CAUTION - when initializing a pointer with some value, don't pass a bare number here as parameter!!!
    it doesn't have NO allocated space, the proggy will compile but then core dump. This is the case with e.g.:
    passValue(123);

    2. CAUTION - initing a pointer with a value doesn't work like e.g.:
    *pVal = val;
    This crashes because the value will be copied to a place that is still not allocated.
  //*/
  void passValue(T val)
  {
    pVal = &val;
  }

  /*
    "ref" can be used like stack variable (using '.')
  //*/
  void passReference(const T& ref)
  {
    pVal = &ref;
  }

  /*
    "ptr" will be a dynamical variable, elements are accessed by using '->'
  //*/
  void passPointer(T* ptr)
  {
    pVal = ptr;
  }

  /*
    output function
  //*/
  void printData()
  {
    if(!pVal) return;

    // in case operator<<() needs here to be overloaded, too
    std::cout << "pVal:\t" << pVal
	      << "\n*pVal:\t" << *pVal << "\n&pVal:\t" << &pVal
	      << "\n*&pVal:\t" << *&pVal << std::endl;
    std::cout << std::endl;
  }
};


/*
  main()
//*/
int main()
{
  // init some objs
  Acceptor<int> a, b, c, d, e, f;

  // init targets
  int value = 123;
  int *pointer =&value;


  // pass-by-value
  std::cout << "1. pass-by-value - value" << std::endl;
  a.passValue(value);
  a.printData();

  std::cout << "pass-by-value - pointer" << std::endl;
  b.passValue(*pointer);
  b.printData();
  std::cout << std::endl;


  // pass-by-reference
  std::cout << "2. pass-by-reference - value" << std::endl;
  c.passReference(value);
  c.printData();

  std::cout << "pass-by-reference - pointer" << std::endl;
  d.passReference(*pointer);
  d.printData();
  std::cout << std::endl;


  // pass-by-pointer
  std::cout << "3. pass-by-pointer - value" << std::endl;
  e.passPointer(&value);
  e.printData();

  std::cout << "pass-by-pointer - pointer" << std::endl;
  f.passPointer(pointer);
  f.printData();
  std::cout << std::endl;


  // done
  std::cout << "READY." << std::endl;
  return 0;
}
