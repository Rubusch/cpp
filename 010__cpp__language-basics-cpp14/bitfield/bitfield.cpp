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

struct BitField
{
  // defines a 'three bit unsigned int field', allows values are: 0,1,2,3,4,5,6,7
  unsigned int bits : 3;
};

struct DerivedBitField
: public BitField
{
  unsigned int another_bits : 2;
};


int main(void)
{
  // initialization with '6'
  cout << "bitfield bf created" << endl;
  BitField bf = { 6 };
  cout << "bf.bits: " << bf.bits << endl;
  cout << endl;

  // increment, now storing '7' as content
  cout << "bitfield bf incremented" << endl;
  ++bf.bits;
  cout << "bf.bits: " << bf.bits << endl;
  cout << endl;

  cout << "bitfield bf incremented, again" << endl;
  ++bf.bits;
  cout << "bf.bits: " << bf.bits << endl;
  cout << endl;

// TODO sizes

    // initialization with '6'
  cout << "derived bitfield dbf created" << endl;
  DerivedBitField dbf = DerivedBitField();
  dbf.bits = 7;
  dbf.another_bits = 2;
  cout << "dbf.bits: " << dbf.bits << ", dbf.another_bits: " << dbf.another_bits << endl;
  cout << endl;

  cout << "READY." << endl;
}
