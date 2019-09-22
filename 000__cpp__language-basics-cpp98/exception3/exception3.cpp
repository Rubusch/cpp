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


#include <iostream>
#include <cstdlib> // exit()
#include <cstring> // strlen()
#include <new> // bad_alloc

signed int strsize(const std::string str)
{
  return str.size() + 1;
}

/*
  some main
//*/
int main()
{
  using namespace std;

  // init
  cout << "init..\n";
  char* str = NULL;
  cout << endl;

  // alloc
  cout << "allocate " << strsize("Hello World!") << " tokens..\n";
  try{
    str = new char[strsize("Hello World!")];
  }catch(bad_alloc&){
    cerr << "ERROR: allocation failed" << std::endl;
    exit(-1);
  }
  cout << endl;

  // set
  cout << "set a value:\n";
  strncpy(str, "Hello World!\0", strsize("Hello World!"));
  cout << "\t" << str << endl << endl;

  // dealloc & reset!
  cout << "delete..\n";
  delete str;
  str = NULL;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
