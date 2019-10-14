/*
  bitfields experienced

  - pointers or non-const references are not possible

  - the type of a bit field can only be integral or enumeration type

  - cannot be a static member

  - no pure rvalues, rvalue-to-lvalue conversion

  - default initialized to '0'

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

struct BitField {
  // defines a 'three bit unsigned int field', allows values are:
  // 0,1,2,3,4,5,6,7
  unsigned int bits : 3;

  virtual ~BitField(){}; // interestingly: w/o virtual dtor, the braced
                         // initializer is working
};

struct DerivedBitField : public BitField {
  // if the specified size of the bit field is greater than the size of its
  // type, the value is limited by the type:
  unsigned int another_bits : 2;
};


int main(void)
{
  // initialization with '6'
  cout << "bitfield bf created" << endl;
  BitField bf; // {} not working, initializer list (...)
  bf.bits = 6;
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

  cout << "sizeof(bf): " << sizeof(bf) << endl
       << "sizeof(bf.bits): ERROR - can't apply sizeof to a bitfield" << endl;
  cout << "&bf: " << &bf << endl
       << "&bf.bits: ERROR - can't get address of a bitfield" << endl;
  cout << endl;

  // derived bitfield
  cout << "derived bitfield dbf created" << endl;
  DerivedBitField dbf = DerivedBitField();
  dbf.bits = 7;
  dbf.another_bits = 2;
  cout << "dbf.bits: " << dbf.bits << ", dbf.another_bits: " << dbf.another_bits
       << endl;
  cout << endl;

  cout << "another derived bitfield adbf created (only one initialization)"
       << endl;
  DerivedBitField adbf = DerivedBitField();
  adbf.bits = 7;
  cout << "adbf.bits: " << adbf.bits
       << ", adbf.another_bits: " << adbf.another_bits << endl;
  cout << endl;

  // note:
  //  printf("bf: 0x%lX", (unsigned long)bf); // ERROR, not possible to read out
  //  bits directly

  cout << "sizeof(bf): " << sizeof(bf) << endl;
  cout << "sizeof(dbf): " << sizeof(dbf) << endl;
  cout << "sizeof(adbf): " << sizeof(adbf) << endl;
  cout << endl;

  cout << "READY." << endl;
}
