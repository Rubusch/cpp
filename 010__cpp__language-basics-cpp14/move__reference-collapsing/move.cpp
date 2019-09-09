/*
  C++11 - rvalue reference, move semantics and perfect forwarding
  (Meyers / item 28)

  When an lvalue is passed as an argument, T is deduced to be an lvalue
  reference. When an rvalue is passed, T is deduced to be a non-reference.

  When a reference to a reference arises in a context where this is permitted
  (e.g. during template instantiation), the references collapse to a single
  reference according to this rule:
  If either reference is an lvalue reference, the result is an lvalue reference.
  Otherwise (i.e., if both are rvalue references) the result is an rvalue
  reference.


  Avoid using 'std::forward' with rvalue references, even worse is the idea of
  using 'std::move' with universal references!!!

  Avoid overloading universal references!!!


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

  - reference collapsing occurs in four contexts: template instantiation, auto
    type generation, creation and use of typedefs and alias declarations, and
    decltype

  - when compilers generate a referene to a reference in a reference collapsing
    context, the result becomes a single reference. If either of the original
    references is an lvalue reference, the result is an lvalue reference.
    Otherwise it's an rvalue reference.

  - universal references are rvalue references in contexts where type deduction
    distinguishes lvalues from rvalues and where reference collapsing occurs

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */


#include <iostream>
#include <vector>

using namespace std;


class Fruit
{
public:
  Fruit() { cout << "CALLED: Fruit::Fruit()" << endl; }
};

template< typename T >
void func(T&& fruit)
{
  cout << "CALLED: func(Fruit&)" << endl;
}

Fruit fruitFactory()
{
  return Fruit();
}


// calls
int main(void)
{
  cout << "rvalue: Fruit factoryFruit = factoryFruit()" << endl;
  Fruit factoryFruit = fruitFactory(); // returning rvalue
  cout << endl;

  cout << "lvalue: Fruit fruit;" << endl;
  Fruit fruit; // an lvalue
  cout << endl;

  cout << "lvalue: func(fruit); // T&& reduced to 'Fruit&'" << endl;
  func(fruit); // an lvalue, T deduced to be an 'Fruit&'
  cout << endl;

  cout << "rvalue: func(Fruit()); // T&& reduced to 'Fruit'" << endl;
  func(Fruit()); // an rvalue, T deduced to be an 'Fruit'
  cout << endl;


  vector<Fruit> vec;
  vec.push_back(factoryFruit);
  cout << "READY." << endl;
}
