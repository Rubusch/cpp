// typecheck.cpp
/*
  Techniques, item 1: Type Check by Assertions

  "Suppose, for instance, you are developing a function for safe casting. You want to cast
  from one type to another, while making sure that information is preserved; larger types
  must not be cast to smaller types."

  The original code snippet is thought for a situation using the very "libaral"
  reinterpret_cast - this didn't work out for me working with gcc 4.3.2, reinterpret_cast
  of a bigger type into a smaller one is not possible (allowed in standard?).

  I could enter a similar situation, though, using the static_cast or typedef. Since I'd
  like to stay in C++, though, I use here the static_cast() for the example.

  resources: Modern C++ Design, Alexandrescu
//*/


#include <iostream>
#include <cassert> // c style assert()


using namespace std;


/*
  do a checked cast
//*/
template<class To, class From>
To checked_cast(From from)
{
  assert(sizeof(From) <= sizeof(To));
  return static_cast<To>(from);
}


/*
  the same cast but unchecked
//*/
template<class To, class From>
To unchecked_cast(From from)
{
  return static_cast<To>(from);
}


/*
  the main..
//*/
int main()
{
  // init
  cout << "init..";
  long long_value = 123123123;
  short short_value = 0;
  cout << "ok.\n";
  cout << endl;


  /*
    cast of bigger type to a smaller type (in case gives WARNING)

    The problem, if the destination type is smaller, is that we will loose data!
    To avoid this, we assert-check the sizeof's of the types to be casted.
  //*/
  cout << "#1: unchecked cast \'long\' (" << long_value << ", " << sizeof(long_value) << " bytes) to \'short\' ("
       << short_value << ", " << sizeof(short_value) << " bytes).\n";
  short_value = unchecked_cast<short>(long_value);
  cout << "ok.\n" << endl;


  /*
     CAUTION:
     The code compiles, but here the cast throws an assertion
  //*/
  cout << "#2: checked cast \'long\' (" << long_value << ", " << sizeof(long_value) << " bytes) to \'short\' ("
       << short_value << ", " << sizeof(short_value) << " bytes).\n";
  short_value = checked_cast<short>(long_value);
  cout << "ok.\n" << endl;


  /*
    INTERESTING:
    The template is defined by two template types, but finally only needs to have
    the destination type. It doesn't need the FULL template section!!
  //*/

  cout << "READY.\n";
  return 0;
}
