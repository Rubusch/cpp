// const.cpp
/*
    D A T A  |  T Y P E



  const char var       = 'x';

  constant type "const char"; no other value possible



        char * p       = "Hello";

  pointer  of variable type; data variable



  const char * p       = "Hello";

  pointer to constant type; initialization of pointee only once, may change
  pointer to other pointee



        char * const p = "Hello";

  constant pointer of "char"; may be initialized several times with different
  values, but cannot change the pointee




  const char * const p = "Hello";

  constant pointer to constant type; can't change pointee, and pointee can't
  change initialized value



  the const casts from "foobar" to char* are not needed, but without we get
  warnings!
//*/

#include <iostream>
using namespace std;


/*
  main
//*/
int main()
{
  //  Testconst<string> tc;
  //  tc.test();

  // constants - will give warnings (char* is deprecated in favor of string!)
  char *variable = const_cast< char* >( "type variable, data variable" );
  const char *const_char = "type constant, data variable";

  /* WON'T BE USED IF THE CODE BELOW IS DEACTIVATED
  char * const char_const = const_cast<char*>("type variable, data constant");
  const char * const constant = "type constant, data constant";
  //*/


  /*
    type variable, data variable
  //*/
  // setting a new content:
  variable = const_cast< char* >( "foobar" ); // POSSIBLE - complete variable


  /*
    type constant, data variable
    Only can be inited with a string!
  //*/
  const_char = "foobar";    // POSSIBLE - constant type, not content!
  // const_char = 12345;    // NOT POSSIBLE: constant type!


  /*
     type variable, data constant
     Could have also been inited with a number!
  //*/
  // char_const = "foobar"; // NOT POSSIBLE: constant content! NOT TYPE!


  /*
    type constant, data constant
    ONLY COULD HAVE BEEN INITED WITH A STRING!
  //*/
  // constant = "foobar";   // NOT POSSIBLE: constant

  cout << "Have a look on the code, and it's comments!" << endl;
  cout << "READY." << endl;
  return 0;
}
