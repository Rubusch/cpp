/*
  C++11 - rvalue reference, move semantics and perfect forwarding
  (Meyers / item 26)

  Use 'std::move' on rvalue referneces and 'std::forward' on
  universal references!!!

  Local objects which could be returned fall under the RVO (return value
  optimization), and should not be moved or forwarded.

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

  - overloading on universal references almost always leads to the universal
    reference overload being called more frequently than expected

  - perfect-forwarding constructors are especially problematic, because they're
    typically better matches than copy constructors for non-const lvalues, and
    they can hijack derived class calls to base class copy and move constructors

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */


#include <iostream>
#include <set>
#include <chrono>

using namespace std;


multiset< string > names;

// the naive approach
void logAndAdd1(const string& name)
{
  auto start = chrono::system_clock::now();
  names.insert(name);
  auto stop = chrono::system_clock::now();

  chrono::duration< double > diff = stop - start;
  cout << "diff: " << diff.count() << endl;;
}


// should be tuned version
// perfect forwarding of universal reference
// problem: overloading of this does not work anymore - catches all!
template< typename T >
void logAndAdd2(T&& name)
{
  auto start = chrono::system_clock::now();
  names.emplace( forward< T >(name) ); // using forward inside emplace()
  auto stop = chrono::system_clock::now();

  chrono::duration< double > diff = stop - start;
  cout << "diff: " << diff.count() << endl;;
}


// alternatives to overloading of universal references
void logAndAddImpl();
{
  auto start = chrono::system_clock::now();
  names.emplace( forward< T >(name) ); // using forward inside emplace()
  auto stop = chrono::system_clock::now();

  chrono::duration< double > diff = stop - start;
  cout << "diff: " << diff.count() << endl;;
}


template< typename T >
void logAndAdd3(T&& name)
{
  logAndAddImpl(forward< T >(name), is_integral< T >());// TODO
}


int main(void)
{
  string petName("Darla");

  cout << "logAndAdd1(const string&)" << endl;

  cout << "pass lvalue" << endl;
  logAndAdd1(petName); // pass lvalue std::string
  cout << endl;

  cout << "pass rvalue" << endl;
  logAndAdd1(string("Persephone")); // pass rvalue std::string
  cout << endl;

  cout << "pass string literal" << endl;
  logAndAdd1("Patty Dog"); // pass string literal
  cout << endl;


  cout << "template< typename T> logAndAdd2(T&&)" << endl;

  cout << "pass lvalue" << endl;
  logAndAdd2(petName); // pass lvalue std::string
  cout << endl;

  cout << "pass rvalue" << endl;
  logAndAdd2(string("Persephone")); // pass rvalue std::string
  cout << endl;

  cout << "pass string literal" << endl;
  logAndAdd2("Patty Dog"); // pass string literal
  cout << endl;


  cout << "template< typename T> logAndAdd3(T&&)" << endl;

  cout << "pass lvalue" << endl;
  logAndAdd3(petName); // pass lvalue std::string
  cout << endl;

  cout << "pass rvalue" << endl;
  logAndAdd3(string("Persephone")); // pass rvalue std::string
  cout << endl;

  cout << "pass string literal" << endl;
  logAndAdd3("Patty Dog"); // pass string literal
  cout << endl;

  cout << "READY." << endl;
}
