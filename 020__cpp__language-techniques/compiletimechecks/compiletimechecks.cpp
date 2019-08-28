// compiletimeerror.cpp
/*
  Techniques, item 2: Provoking a Compile-time Error

  "The idea" here "is to pass the compiler a language construct that is legal for a
  nonzero expression and illegal for an expression that evaluates to zero. This way,
  if you pass an expression that evaluates to zero, the compiler will signal a
  compile-time error."

  Annotation: in the book the makro tries to create an array unnamed[1] or unnamed[0] -
  this doesn't have the desired effekt using g++ 4.3.2, thus I changed the '0' to '-1'

  resources: Modern C++ Design, Alexandrescu
//*/


#include <iostream>


using namespace std;


// the new construct to provide the compile-time error
#define STATIC_CHECK(expr) { char unnamed[(expr) ? 1 : -1]; }


// test it
template<class To, class From>
To checked_cast(From from)
{
  STATIC_CHECK(sizeof(From) <= sizeof(To));
  return static_cast<To>(from);
}


// do it unchecked
template<class To, class From>
To unchecked_cast(From from)
{
  return static_cast<To>(from);
}


/*
  another main..
//*/
int main()
{
  cout << "init..";
  long long_value = 123123123;
  short short_value = 0;
  cout << "ok.\n";
  cout << endl;


  /*
    cast of bigger type to smaller type (in case gives WARNING)
  //*/
  cout << "#1: unchecked cast \'long\' (" << long_value << ", " << sizeof(long_value) << " bytes) to \'short\' ("
       << short_value << ", " << sizeof(short_value) << " bytes).\n";
  short_value = unchecked_cast<short>(long_value);
  cout << "ok.\n" << endl;


  /*
     CAUTION: THIS CODE SHOULD NOT COMPILE!

     Here the cast of a bigger type to a smaller one leads to a compile-time error
  //*/
  cout << "#2: checked cast \'long\' (" << long_value << ", " << sizeof(long_value) << " bytes) to \'short\' ("
       << short_value << ", " << sizeof(short_value) << " bytes).\n";
  short_value = checked_cast<short>(long_value);
  cout << "ok.\n" << endl;
  //*/


  cout << "READY.\n";
  return 0;
}
