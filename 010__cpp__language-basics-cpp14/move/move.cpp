/*
  C++11 - rvalue reference, move semantics and perfect forwarding (Meyers / item 23)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  move semantics: makes it possible for compilers to replace expensive copying
  operations with less expensive moves. In the same way that copy constructors
  and copy assignment operators give you control over what it means to copy
  objects, move constructors and move assignment operators offer control over
  the semantics of moving. Move semantics also enables the creation of move-only
  types, such as 'std::unique_ptr', 'std::future' and 'std::thread'.

  perfect forwarding: makes it possible to write function templates that take
  arbitrary arguments and forward them to other functions such that the target
  funcitons receive exactly the same arguments as were passed to the forwarding
  functions


  CONCLUSION

  - 'std::move' performs an unconditional cast to an rvalue. In and of itself,
  it doesn't move anything

  - 'std::forward' casts its argument to an rvalue only if that argument is
  bound to an rvalue

  - neither 'std::move' nor 'std::forward' do anything at runtime

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


int main(void)
{
  // TODO

  cout << "READY." << endl;
}
