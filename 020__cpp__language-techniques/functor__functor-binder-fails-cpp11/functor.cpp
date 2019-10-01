// functor.cpp
/*
  A more sophisticated implementation of a functor using a binder.

  (taken from Alexandrescu, 2001)
//*/

#include "functor.hpp"

#include <iostream>
#include <exception>


/*
  function to test the bind
//*/
const char* function(int i, int j)
{
  std::cout << "function(" << i << ", " << j << ") called\n";
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
  Functor< const char*, TL::Typelist< char, int > > func1(function);
  cout << endl;

  /*
    set up another functor using "bind" to bind to the first functor
    -> the function will be called with one parameter of the first
    and another parameter of the second Functor
  // */
  try {
    cout << "second function\n";
    Functor< string, TL::Typelist< double > > func2( BindFirst(func1, 10));
    cout << endl;

    // prints: "Fun(10, 15) called"
    cout << "function call\n";
    func2(15);
    cout << endl;
  } catch (exception &e) {
    cout << "!!! AN EXCEPTION WAS CAUGHT (as expected)" << endl;
    cout << "!!! " << e.what() << endl;
    cout << "!!! the BindFirst(func1, 10) failed" << endl;
  }


  cout << "READY.\n";
  return 0;
}
