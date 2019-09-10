/*
  bitfields experienced

  this should be a bitfield experiencing ground, but Scott Meyers mentiones
  bitfields in one item, so it's refered here, to be kept in mind


  NOTE:
  C++11 - perfect forwarding failure cases (Meyers / item 30)

  CONCLUSION (Scott Meyers)

  - perfect forwarding fails when template type eduction fails or when it
    deduces the wrong type

  - the kinds of arguments that lead to perfect forwarding failure are braced
    initializers, null pointers expressed as 0 or NULL, declaration-only
    integral 'const static' data members, template and overloaded function
    names, and bitfields

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */

#include <iostream>

using namespace std;


int main(void)
{
  // TODO

  cout << "READY." << endl;
}
