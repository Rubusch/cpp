// exception.cpp
/*
  Demonstrates the usage of a own defined eception class

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


#include <cstdlib>   // exit()
#include <cstring>   // strlen()
#include <exception> // exception
#include <iostream>


/*
  some class..
//*/
class SomeClass
{
public:
  // definition of an exception as an inner class
  class BadAnimalException : public std::exception
  {
  public:
    BadAnimalException(){};
    ~BadAnimalException() throw() {}
    const char *what() const throw()
    {
      return "Some Baaaaaaaaaaad Animal Appeared!";
    }
  };

  // usage declaration
  void someFunc() throw(BadAnimalException);
};


// usage defintion
void SomeClass::someFunc() throw(SomeClass::BadAnimalException)
{
  std::cout << "someFunc() will throw an exception..\n";
  // in case of ... throw
  throw BadAnimalException();
}


/*
  some main
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  SomeClass sc;
  cout << endl;

  try {
    sc.someFunc();
  } catch (SomeClass::BadAnimalException &ex) {
    cerr << "Bad Animal Exception: " << ex.what() << endl;
  }

  cout << endl;
  cout << "try again..\n";
  try {
    sc.someFunc();
  } catch (SomeClass::BadAnimalException &) {
    cerr << "Bad Animal Exception again..\n";
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
