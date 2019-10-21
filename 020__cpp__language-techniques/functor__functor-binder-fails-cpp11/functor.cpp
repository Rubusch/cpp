// functor.cpp
/*
  A more sophisticated implementation of a functor using a binder.

  (taken from Alexandrescu, 2001)
//*/

#include "functor.hpp"

#include <exception>
#include <functional> /* std::bind() */
#include <iostream>


/*
  function to test the bind
  NOTE: if the function is called 'function()' names will collide with the
'#include <functional>'
//*/
const char *my_function(int i, int j)
{
  std::cout << "CALLED: my_function(" << i << ", " << j << ")" << std::endl;
  return nullptr;
}


/*
  main...
//*/
int main()
{
  using namespace std;

  // set up a functor
  cout << "1. function" << endl;
  Functor< const char *, TL::Typelist< char, int > > func1(
      my_function); // TODO function?
  cout << endl;

  /*
    set up another functor using "bind" to bind to the first functor
    -> the function will be called with one parameter of the first
    and another parameter of the second Functor
  // */
  try {
    cout << "2. function" << endl;
    Functor< string, TL::Typelist< double > > func2(BindFirst(func1, 10));
    // prints: "Fun(10, 15) called"
    cout << "function call" << endl;
    func2(15); // problematic for binder
  } catch (exception &e) {
    cout << "!!! AN EXCEPTION WAS CAUGHT (as expected)" << endl;
    cout << "!!! " << e.what() << endl;
    cout << "!!! the BindFirst(func1, 10) failed" << endl;
  }
  cout << endl;

  cout << "3. function (using std::bind() functor) - one solution in modern C++"
       << endl;
  using namespace std::placeholders; // don't forget the using declaration!!!
  auto func3 = std::bind(
      func1, 10,
      _1); // leave the 2. arg open (which is the first _1 variable in bind)
  func3(15);
  cout << endl;

  cout << "4. function (using std::bind() functor) - another solution in "
          "modern C++"
       << endl;
  auto func4 = [&](int arg2) { func1(10, arg2); };
  func4(15);
  cout << endl;

  cout << "READY." << endl;
  return 0;
}
