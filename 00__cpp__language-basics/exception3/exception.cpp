// exception.cpp
/*
  Demonstrates another example of usage of the exceptions

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
