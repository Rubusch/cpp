// emptytype.cpp
/*
  The "don't care" type!

  "EmptyType is a legal type to inherit from, and you can pass around
  values of type EmptyType.

  You can use this insipid type as a default ('don't care') type for
  a template."

  resources: Modern C++ Design, Alexandrescu
//*/


#include <iostream>


// Implementation of the EmptyType
struct EmptyType {
} final;


/*
  main..
//*/
int main()
{
  using namespace std;

  // instantiation of "nothing"
  // (warnings are turned off, since 'et' is unused here)
  EmptyType et;

  cout << "The EmptyType can be used as an empty type to check in inheritance."
       << endl;

  cout << "READY.\n";
  return 0;
}
