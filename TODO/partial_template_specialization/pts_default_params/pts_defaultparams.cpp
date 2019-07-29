// pts_defaultparams.cpp
/*
  demonstrates templates with default template parameters
//*/


#include <iostream>

using namespace std;


/*  // cpp0x:
#define MACRO 123
/*/ // cpp11:
constexpr auto MACRO=123;
//*/

/*
  template class with default template parameter
//*/
template< int value=MACRO >
class SomeClass
{
public:
  SomeClass()
  {
    cout << "SomeClass< int >::SomeClass() - value: " << value << endl;
  }
};


/*
  ...main
//*/
int main()
{
  using namespace std;

  cout << "using default value:\n";
  SomeClass<> sc1;
  cout << endl;

  cout << "setting a value - " << 777 << ":\n";
  SomeClass< 777 > sc2; // has to be a number, not a variable!!!
  cout << endl;

  cout << "READY.\n";
  return 0;
}
