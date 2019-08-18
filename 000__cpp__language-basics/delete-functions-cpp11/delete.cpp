/*
  C++11 - prefer delete functions to private undefined (Meyers / item 11)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - prefer deleted functions to private undefined ones

  - any function may be deleted, including non-member functions and template
    instantiations

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


int main(void)
{
// TODO

  cout << "READY." << endl;
}

