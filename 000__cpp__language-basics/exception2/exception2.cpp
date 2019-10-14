// exception.cpp
/*
  Demonstrates another example of usage of the exceptions

  ---


  EXCEPTIONS

  * If a function should forward all exceptions if it is not supposed to handle
    the exceptions or to absorb exceptions.

  * Destructors, operator delete() or operator delete[]() are supposed to handle
    exceptions and should never throw or forward an exception.

  * Basic Exception Guarantee (Dave Abrahams): Make sure that in presence of
    exceptions there are no resource leaks, already allocated memory must be
    freed at exception handling.

  * Advanced Exception Guarantee (Dave Abrahams): Keep the state unchanged at
    presence of exceptions, i.e. "go back to before the exception was thrown"
    (not possible with streams or already placed output.

  * Absolute Guarantee (Herb Sutter): Make sure no exceptions are needed.



  DEFINITIONS

  * exception safety: code still works correctly in presence of exceptions

  * exception neutrality: forwards all exceptions without integrity problems



  RESOURCES

  * Exceptional C++, Herb Sutter, 2000

//*/


#include <cstdlib> // exit()
#include <iostream>


template < class T >
class SomeClass
{
private:
  T *ptr;

public:
  // ctor
  SomeClass(T t);

  // dtor - since we have a dynamic pointer!
  ~SomeClass();

  T getVal();
};

template < class T >
SomeClass< T >::SomeClass(T t) : ptr(NULL)
{
  std::cout << "\tSomeClass::SomeClass() - ctor\n";

  // allocate
  try {
    ptr = new T;
  } catch (...) { // ... catches every exception
    std::cerr << "ERROR: allocation failed" << std::endl;
    delete ptr;
    throw;

    exit(-1);
  }

  // init
  *ptr = t;
}

template < class T >
SomeClass< T >::~SomeClass()
{
  std::cout << "\tSomeClass::~SomeClass() - dtor\n";

  // free memory - avoid exceptions in the dtor
  delete ptr;
  ptr = NULL;
}

template < class T >
T SomeClass< T >::getVal()
{
  std::cout << "\tSomeClass::getVal()\n";

  try {
    if (NULL == ptr) {
      throw "no delete necessary!";
    }
    return *ptr;
  } catch (char const *str) { // catches a thrown string exception
    std::cerr << "ERROR: " << str << std::endl;
  }
  return "empty";
}


/*
  some main
//*/
int main()
{
  using namespace std;

  cout << "instantiate a class\n";
  SomeClass< string > sc("Hello World!");
  cout << endl;

  cout << "get value()\n";
  cout << sc.getVal() << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
