/*
  C++11 - prefer scoped enums to unscoped enums (Meyers / item 10)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)

  scoped enums - C++11-style enums, e.g. 'enum class {}'

  unscoped enums - C++98-style enums, e.g. 'enum {}'


  conclusion:

  - C++98-style enums are now known as unscoped enums

  - enumerators of scoped enums are visible only within the enum, they convert
    to other types only with a cast

  - both scoped an unscoped enums support specification of the underlying type;
    the default underlying type for scoped enums is int; unscoped enums have no
    default underlying type

  - scoped enums may always be forward-declared; unscoped enums may be
    forward-declared only if their declaration specifies an underlying type

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


int main(void)
{
/*
  cout << "C++98-style enum" << endl;
  enum Color { black, white, green };
  auto white = false; // does not compile
/*/
  cout << "C++11-style enum" << endl;
  enum class Color { black, white, green };
  auto white = false; // works
// */

  cout << "some enum operations" << endl;
  Color clr1 = Color::white; // works
  auto clr2 = Color::white; // works
  cout << endl;

  cout << "enum class with specific type" << endl;
  enum class Status: std::uint32_t { good = 0
                                     , failed = 1
                                     , incomplete = 100
                                     , corrupt = 200
                                     , audited = 500
                                     , indeterminate = 0xffffffff
  };


// TODO userinfo and typed example

  cout << "READY." << endl;
}
