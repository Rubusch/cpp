/*
  C++11 - decltype (Meyers / item 3)

  template< typename T >
  void func(ParmType param);

  func(expr)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)

  T         - template type

  ParamType - parameter type, basically the template type with certain
              adornments, e.g. const, reference, pointer, etc.

  expr      - expression type, the deducted type from the ParamType in the
              expression


  conclusion:

  - decltype almost always yields the type of a variable or expression without
    any modifications

  - for lvalue expressions of type T other than names, decltype always reports a
    type of T&

  - C++14 supports decltype(auto), which, like auto, deduces a type from its
    initializer, but it performs the type deduction using the decltype rules

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


int main(void)
{
  // TODO

  cout << "READY." << endl;
}

