// exception.cpp
/*
  Demonstrates the usage of a own defined eception class
//*/


#include <iostream>
#include <exception> // exception
#include <cstdlib> // exit()
#include <cstring> // strlen()


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
    BadAnimalException() {};
    ~BadAnimalException() throw() {}
    const char* what() const throw()
    {
      return "Some Baaaaaaaaaaad Animal Appeared!";
    }
  };

  // usage declaration
  void someFunc() throw (BadAnimalException);
};


// usage defintion
void SomeClass::someFunc()
  throw (SomeClass::BadAnimalException)
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

  try{
    sc.someFunc();
  }catch(SomeClass::BadAnimalException& ex){
    cerr << "Bad Animal Exception: " << ex.what() << endl;
  }

  cout << endl;
  cout << "try again..\n";
  try{
    sc.someFunc();
  }catch(SomeClass::BadAnimalException&){
    cerr << "Bad Animal Exception again..\n";
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
