// pts_defaultparams.cpp
/*
  demonstrates templates with default template parameters
//*/


#include <iostream>


#define MACRO 123


/*
  template class with default template parameter
//*/
template< int value=MACRO >
class SomeClass
{
public:
  SomeClass()
  {
    std::cout << "SomeClass< int >::SomeClass() - value: " << value << std::endl;
  }
};


/*
  ...main
//*/
int main()
{
  using namespace std;

  std::cout << "using default value:\n";
  SomeClass<> sc1;
  cout << endl;

  std::cout << "setting a value - " << 777 << ":\n";
  SomeClass< 777 > sc2; // has to be a number, not a variable!!!
  cout << endl;

  std::cout << "READY.\n";
  return 0;
}
