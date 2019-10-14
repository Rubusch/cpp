/*
  C++11 - prefer nullptr (Meyers / item 8)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - prefer nullptr to 0 and NULL

  - avoid overloading on integral and pointer types

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


void func(int i) { cout << "CALLED: void func(int i);" << endl; }
void func(bool b) { cout << "CALLED: void func(bool b);" << endl; }
void func(void *vp) { cout << "CALLED: void func(void* vp);" << endl; }

int main(void)
{
  // different overloads
  cout << "func(0)" << endl;
  func(0);
  cout << endl;

  // might not compile (NULL is ambiguous)! typically calls int overload
  cout << "func(NULL) - might not compile" << endl;
  //  func(NULL);
  cout << endl;

  cout << "func(nullptr)" << endl;
  func(nullptr);
  cout << endl;

  // nullptr offers better recognition as pointer type 'null' than NULL, but
  // especially in combination with 'auto' avoid overloading of different
  // pointer types in functions

  cout << "READY." << endl;
}
