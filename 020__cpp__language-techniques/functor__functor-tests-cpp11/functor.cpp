// functor.cpp
/*
  A more sophisticated implementation of a functor using a binder.

  Adjusted and modified to rather modern C++ by Lothar Rubusch (2018).

  RESOURCE:
  * Alexandrescu, 2001
//*/


#include <iostream>


#include "functor.hpp"


/*
  function to test the bind
//*/
std::string function(int i, int j)
{
  std::cout << "function(" << i << ", " << j << ") called\n";
  return "0";
}


/*
  main...
//*/
int main()
{
  using namespace std;

  // set up a functor
  cout << "first function\n";
  auto func1 = Functor< string, TL::Typelist< int, int > >(function);
  cout << endl;

  /*
    set up another functor using "bind" to bind to the first functor
    -> the function will be called with one parameter of the first
    and another parameter of the second Functor
  //*/
  cout << "second function\n";
  auto func2 = Functor< string, TL::Typelist< int > >( BindFirst(func1, 10));
  cout << endl;

  // prints: "Fun(10, 15) called"
  cout << "function call\n";
  func2(15);
  cout << endl;


  cout << "READY.\n";
  return 0;
}
