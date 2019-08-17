/*
  C++11 - prefer alias declarations to typedef (Meyers / item 9)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - typedefs don't support templatization, but alias declaration (using) do

  - alias templates avoid the "::type" suffix and, in templates the "typename"
    prefix often required to refer to typedefs

  - C++14 offers alias templates for all the C++11 type traits transformations

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


int main(void)
{
// TODO

  cout << "READY." << endl;
}

