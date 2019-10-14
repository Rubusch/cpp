/*
  C++11 - difference between universal reference and rvalue reference
  (Meyers / item 24)



  DEFINITIONS (by Scott Meyers)

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



  DEFINITIONS (by cppreference.com)

  glvalue ('generalized' lvalue) is an expression whose evaluation determines
          the identity of an object, bit-field, or function

  prvalue ('pure' rvalue) is an expression whose evaluation either
        - computes the value of the operand of an operator (such prvalue has
          no result object), or
        - initializes an object or a bit-field (such prvalue is said to have
          a result object). All class and array prvalues have a result object
          even if it is discarded. In certain contexts, temporary
          materialization occurs to create a temporary as the result object;

  xvalue (an 'eXpiring' value) is a glvalue that denotes an object or bit-field
          whose resources can be reused

  lvalue (so-called, historically, because lvalues could appear on the
          left-hand side of an assignment expression) is a glvalue that is not
          an xvalue
          examples: *a, --a, ++a

  rvalue (so-called, historically, because rvalues could appear on the
          right-hand side of an assignment expression) is a prvalue or an xvalue
          examples: &a, a--, a++

  Names of rvalue reference variables are lvalues and have to be converted to
  xvalues to be bound to the function overloads that accept rvalue reference
  parameters, which is why move constructors and move assignment operators
  typically use std::move
  One exception is when the type of the function parameter is rvalue reference
  to type template parameter ("forwarding reference" or "universal reference"),
  in which case std::forward is used instead.



  CONCLUSION

  - if a function template parameter has type T&& for a deduced type T, or if an
    object is declared using auto&&, the parameter or object is a universal
    reference

  - if the form of the type declaration isn't precisely type&&, or if type
    deduction does no occur, type&& denotes an rvalue reference

  - universal referencese correspond to rvalue references if they're initialized
    with rvalues. They correspond to lvalue references if they're initialized
    with lvalues

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;


class Some
{
public:
  Some() { cout << "Some(), ctor" << endl; }
};

void func(Some &&param) // rvalue reference, declaration
{
  cout << "func(Some&&), rvalue reference" << endl;
}

// declarations
template < typename T > // rvalue reference
void func(vector< T > &&param)
{
  cout << "func(vector< T >&&), addr vec: " << &param << endl;
}

template < typename T > // universal reference (forwarding reference)
void func(T &&param)
{
  cout << "func(T&&)" << endl;
}


int main(void)
{

  cout << "rvalue reference" << endl;
  Some &&var1 = Some(); // rvalue reference
  cout << "addr var1: " << &var1 << endl;
  cout << endl;

  cout << "universal reference" << endl; // auto&& or T&& are rather..
  auto &&var2 = var1; // universal reference (forwarding reference)
  cout << "addr var2: " << &var2 << endl;
  cout << endl;


  cout << "READY." << endl;
}
