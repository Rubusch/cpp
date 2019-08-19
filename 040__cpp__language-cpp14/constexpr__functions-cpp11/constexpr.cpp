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


/*
  the C++ standard library provides std::pow(), which is the mathematical
  functionality we need, but, for our purposes, there are two problems with it.
  First, std::pow() works on floating-point types, and we need an integral
  result. Second, std::pow() isn't constexpr (i.e. guaranteed to return a
  compile-time result when called with compile-time values).
 */

/* // C++11
constexpr
int pow(int base, int exp) noexcept
{
  return (exp == 0 ? 1 : base * pow(base, exp - 1));
}
/*/ // C++ 14
constexpr int pow(int base, int exp) noexcept
{
  auto result = 1;
  for (int idx=0; idx < exp; ++idx) result *= base;
  return result;
}
// */


int main(void)
{
  // demostrates constexpr functions


  // shifting the computation of the power of 'base' to compile time
  cout << "printing the computation already done in compile time: " << endl;
  constexpr auto numConds = 7;
  cout << pow(3, numConds) << endl;
  cout << endl;


  // could be used for array configuration at compile time
  // (resource acquisition speed up at runtime)
  cout << "use constexpr function for array initialization: " << endl;
  std::array<int, pow(3, numConds)> results;
  cout << "array.size(): " << results.size() << endl;
  cout << endl;


  // CONCLUSION:
  // - constexpr functions can be used in contexts that demand compile-time
  //   constants
  //
  // - when a constexpr function is called with one or more values that are not
  //   known during compilation, it acts like a normal function, computing its
  //   result at runtime


  cout << "READY." << endl;
}

