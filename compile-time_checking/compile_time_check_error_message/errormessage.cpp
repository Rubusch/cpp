// errormessage.cpp
/*
  Techniques, item 3: Provoking Compile-time Errors and Providing a Error Message

  Manipulating the Error Messages: 
  "The problem with" the approach getting compile-time errors "is that the error message 
  you receive is not terribly informative. 'Cannot create array of size zero' does not 
  suggest 'Type char is too narrow to hold a pointer.' It is very hard to provide customized 
  error messages portably. Error messages have no rules that they must obey; it's all up 
  to the compiler."

  Taken from "Modern C++ Design", Alexandrescu
//*/


#include <iostream>


using namespace std;


// new items to support an error message
template<bool> struct CAUTION_type_too_small_to_cast_to;
template<> struct CAUTION_type_too_small_to_cast_to<true>{};


// provoke the compile-time error
#define STATIC_CHECK(expr) (CAUTION_type_too_small_to_cast_to<(expr) != 0>())


// check and cast
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
  main main..
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
