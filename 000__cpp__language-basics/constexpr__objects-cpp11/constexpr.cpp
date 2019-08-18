/*
  C++11 - prefer constexpr whenever possible (Meyers / item 15)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)

  literal   - a fixed value, thus compile time constant i.e. known at compile time
              (a literal type is a type defined at compile time)


  conclusion:

  - constexpr objects are const and are initialized with values known during
    compilation

  - constexpr functions can produce compile-time results when called with
    arguments whose values are known during compilation

  - constexpr objects and functions may be used in a wider range of contexts
    than non-constexpr objects and functions

  - constexpr is part of an object's or function's interface

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <array>

using namespace std;


int main(void)
{
  // demostrates constexpr objects


  // 1. the problem:
  int size1 = 10; // size1's value not known at compile time, neither can't be derrived
//  constexpr auto arraySize1 = size1; // ERROR! size1 is not useable in a constant expression
//  std::array<int, size1> data1; // ERROR! same problem


  // 2. constexpr:
  constexpr auto size2 = 10;
  constexpr auto arraySize2 = size2; // OK
  std::array<int, size2> data2; // OK


  // 3. 'const' doesn't offer the same guarantee as 'constexpr'
  int size3 = 10; // must be initialized
  const auto arraySize3 = size3; // OK
//  std::array<int, arraySize3> data3; // ERROR!

  // a 'const' can't be used in this literal expression, since a 'const' needs
  // not to be initialized!


  // CONCLUSION:
  // - all constexpr objects are const, but not all const objects are constexpr
  //
  // - constexpr functions can be used in contexts that demand compile-time
  //   constants
  //
  // - when a constexpr function is called with one or more values that are not
  //   known during compilation, it acts like a normal function, computing its
  //   result at runtime


  cout << "READY." << endl;
}

