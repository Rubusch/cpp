/*
  C++11 - prefer const_iterators to iterators (Meyers / item 13)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - prefer const_iterators to iterators

  - in maximally generic code, prefer non-member versions of begin, end, rbegin,
    etc., over their member function counterparts

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


int main(void)
{
  // TODO

  cout << "READY." << endl;
}

