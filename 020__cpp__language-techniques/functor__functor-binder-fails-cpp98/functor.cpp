// functor.cpp
/*
  A more sophisticated implementation of a functor using a binder.

  (taken from Alexandrescu, 2001)
//*/


#include <iostream>


#include "functor.hpp"


/*
  function to test the bind
//*/
const char *my_function(int i, int j)
{
  std::cout << "CALLED: my_function(" << i << ", " << j << ")\n";
  return 0;
}


/*
  main...
//*/
int main()
{
  using namespace std;

  // set up a functor
  cout << "first function\n";
  Functor< const char *, TYPELIST_2(char, int) > func1(my_function);
  cout << endl;

  /*
    set up another functor using "bind" to bind to the first functor
    -> the function will be called with one parameter of the first
    and another parameter of the second Functor
  //*/
  cout << "second function\n";
  Functor< string, TYPELIST_1(double) > func2(BindFirst(func1, 10));
  cout << endl;

  // prints: "Fun(10, 15) called"
  cout << "function call\n";
  func2(15);
  cout << endl;


  cout << "READY.\n";
  return 0;
}
