/*
  C++11 - template type deduction (Meyers / item 1)

  template< typename T >
  void func(ParmType param);

  func(expr)

  ---
  T         - template type
  ParamType - parameter type, basically the template type with certain adornments, e.g. const, reference, pointer, etc.
  expr      - expression type, the deducted type from the ParamType in the expression


  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


// declaration
template< typename T > void funcPlain(T);
template< typename T > void funcPointer(T*);
template< typename T > void funcReference(T&);


// definition
template< typename T >
void funcPlain(T param)
{
  cout << "T: " << endl;
}

template< typename T >
void funcPointer(T* param)
{
  cout << "T*: " << endl;
}

template< typename T >
void funcReference(T& param)
{
  cout << "T&: " << endl;
}


int main(void)
{
  int x = 27;
  const int cx = x;
  const int& rx = x;

  funcPlain<int>(x);
  funcPlain<int>(cx);
  funcPlain<int>(rx);

  cout << "READY." << endl;
}
// TODO
