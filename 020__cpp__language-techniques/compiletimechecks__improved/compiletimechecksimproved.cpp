// improvederrormessage.cpp
/*
  Techniques, item 4: Provoking Compile-time Errors with an Improved Error
Message (THIS IS HIGHLY COMPILER DEPENDENT!)

  "An idea so to pass an additional parameter to STATIC_CHECK and somehow make
that parameter appear in the error message. The disadvantage that remains is
that the custom error message you pass must be a legal C++ identifier (no
spaces, cannot start with a digit, and so on). This line of thought leads to an
improved CompileTimeError, as shown in the following code. Actually, the name
CompileTimeError is no longer suggestive in the new context; as you'll see in a
minute, CompileTimeChecker makes more sense."

  Annotation, this didn't work out on the g++ 4.3.2 - the basic idea is, that in
case the compiler has to perform the cast from a bigger type to a smaller one,
it enters the loop to perform the sizeof() in checked_cast(). To perform the
sizeof() it would have to convert 'struct CompileTimeChecker' and 'class
ERROR_Destination_Type_Too_Narrow' which isn't possible. Therefore - at some
compilers a message would be: "Error: Cannot convert
ERROR_Destination_Type_Too_Narrow to CompileTimeChecker<false>"

  On g++ the message is: "error: invalid application of ‘sizeof’ to a function
type". Hence no improvement!! =/

  resources: Modern C++ Design, Alexandrescu
//*/


#include <iostream>


using namespace std;


// items to support the error information
template < bool >
struct CompileTimeChecker {
  CompileTimeChecker(...);
};

template <>
struct CompileTimeChecker< false > {
};


// check and cast
template < class To, class From >
To checked_cast(From from)
{
  {
    class ERROR_Destination_Type_Too_Narrow
    {
    };
    ( void )sizeof(CompileTimeChecker< (sizeof(From) <= sizeof(To)) >(
        ERROR_Destination_Type_Too_Narrow()));
  }
  return static_cast< To >(from);
}


// cast unchecked
template < class To, class From >
To unchecked_cast(From from)
{
  return static_cast< To >(from);
}


/*
  main
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
  cout << "#1: unchecked cast \'long\' (" << long_value << ", "
       << sizeof(long_value) << " bytes) to \'short\' (" << short_value << ", "
       << sizeof(short_value) << " bytes).\n";
  short_value = unchecked_cast< short >(long_value);
  cout << "ok.\n" << endl;


  /*
     CAUTION: THIS CODE SHOULD NOT COMPILE!

     Here the cast of a bigger type to a smaller one leads to a compile-time
  error
  //*/
  cout << "#2: checked cast \'long\' (" << long_value << ", "
       << sizeof(long_value) << " bytes) to \'short\' (" << short_value << ", "
       << sizeof(short_value) << " bytes).\n";
  short_value = checked_cast< short >(long_value);
  cout << "ok.\n" << endl;
  //*/


  cout << "READY.\n";
  return 0;
}
