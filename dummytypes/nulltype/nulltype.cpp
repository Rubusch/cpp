// nulltype.cpp
/*
  The "not interesting" type!

  "You usually don't create objects of type NullType - its only use is to indicate
  'I am not an interesting type.'"

  Taken from "Modern C++ Design", Alexandrescu
//*/


#include <iostream>


// the null-type
class NullType{};


int main()
{
  using namespace std;

  // instance of the NullType
  NullType nt;

  cout << "The NullType can be used as Null element or termination and can be checked." << endl;

  cout << "READY.\n";
  return 0;
}
