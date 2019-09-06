/*
  C++11 - rvalue reference, move semantics and perfect forwarding (Meyers / item 23)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)

  universal reference - the type of the function parameter is rvalue reference
              to type template parameter


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


  Names of rvalue reference variables are lvalues and have to be converted to
  xvalues to be bound to the function overloads that accept rvalue reference
  parameters, which is why move constructors and move assignment operators
  typically use std::move
  One exception is when the type of the function parameter is rvalue reference
  to type template parameter ("forwarding reference" or "universal reference"),
  in which case std::forward is used instead.

  CONCLUSION

  - 'std::move' performs an unconditional cast to an rvalue. In and of itself,
  it doesn't move anything

  - 'std::forward' casts its argument to an rvalue only if that argument is
  bound to an rvalue

  - neither 'std::move' nor 'std::forward' do anything at runtime

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */

#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;


int main(void)
{
  string str = "hello";
  vector< string > vec;

  cout << "vec.push_back( str )" << endl;
  vec.push_back( str );
  cout << "after, str = '" << str << "'" << endl;
  cout << endl;

  cout << "vec.push_back( std::move( str ) )" << endl;
  vec.push_back( std::move(str) );
  cout << "after, str = '" << str << "'" << endl;
  cout << endl;

  cout << "content of vec: '" << vec[0] << "', '" << vec[1] << "'" << endl;


  cout << "READY." << endl;
}
