// functor.cpp
/*
  A more sophisticated implementation of a functor using a binder.

  (taken from Alexandrescu, 2001)
//*/

#include "functor.hpp"

#include <iostream>
#include <exception>
#include <functional> /* std::bind() */


/*
  function to test the bind
  NOTE: if the function is called 'function()' names will collide with the '#include <functional>'
//*/
const char* my_function(int i, int j)
{
  std::cout << "CALLED: my_function(" << i << ", " << j << ")" << std::endl;
  return 0;
}


/*
  main...
//*/
int main()
{
  using namespace std;

  // set up a functor
  cout << "first function" << endl;
  Functor< const char*, TL::Typelist< char, int > > func1(my_function); // TODO function?
  cout << endl;

  /*
    set up another functor using "bind" to bind to the first functor
    -> the function will be called with one parameter of the first
    and another parameter of the second Functor
  // */
  try {
    cout << "second function" << endl;
    Functor< string, TL::Typelist< double > > func2( BindFirst(func1, 10));
    cout << endl;

    // prints: "Fun(10, 15) called"
    cout << "function call" << endl;
    func2(15); // problematic for binder
    cout << endl;
  } catch (exception &e) {
    cout << "!!! AN EXCEPTION WAS CAUGHT (as expected)" << endl;
    cout << "!!! " << e.what() << endl;
    cout << "!!! the BindFirst(func1, 10) failed" << endl;
    cout << endl;
  }
/*
  try {
    cout << "third function" << endl;
    Functor< string, TL::Typelist< double > > func2( BindFirst(func1, 10));
//    Functor< string, TL::Typelist< double > > func2( std::bind(func1, _1, 10) );
    cout << endl;

    // prints: "Fun(10, 15) called"
    cout << "function call" << endl;
    func2(15); // problematic for binder
    cout << endl;
  } catch (exception &e) {
    cout << "!!! AN EXCEPTION WAS CAUGHT (as expected)" << endl;
    cout << "!!! " << e.what() << endl;
    cout << "!!! the BindFirst(func1, 10) failed" << endl;
    cout << endl;
  }
// */

  cout << "READY." << endl;
  return 0;
}
