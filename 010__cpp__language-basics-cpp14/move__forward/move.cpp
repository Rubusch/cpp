/*
  C++11 - rvalue reference, move semantics and perfect forwarding
  (Meyers / item 25)

  Use 'std::move' on rvalue referneces and 'std::forward' on
  universal references!!!

  Local objects which could be returned fall under the RVO (return value
  optimization), and should not be moved or forwarded.


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

  - apply 'std::move' to rvalue references and 'std::forward' to universal
    references the last time each is used

  - do the same thing for rvalue references and universal references being
    returned from functions that return by value

  - never apply 'std::move' or 'std::forward' to local objects if they would
    otherwise be eligible for the return value optimization!!!

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */

#include <iostream>
#include <memory>
#include <utility>

using namespace std;

struct Overload {
  Overload(int &&elem)
  {
    cout << "rvalue overload, elem = " << elem << " [" << &elem << "]" << endl;
  }
  Overload(int &elem)
  {
    cout << "lvalue overload, elem = " << elem << " [" << &elem << "]" << endl;
  }
};

class Forwarder
{
private:
  Overload o1_, o2_, o3_;

public:
  template < class T1, class T2, class T3 >
  Forwarder(T1 &&t1, T2 &&t2, T3 &&t3)
      : o1_{std::forward< T1 >(t1)}, o2_{std::forward< T2 >(t2)},
        o3_{std::forward< T3 >(t3)}
  {
  }
};

template < class T, class U >
std::unique_ptr< T > make_unique1(U &&u)
{
  return std::unique_ptr< T >(new T(std::forward< U >(u)));
}

template < class T, class... U >
std::unique_ptr< T > make_unique2(U &&... u)
{
  return std::unique_ptr< T >(new T(std::forward< U >(u)...));
}


int main(void)
{
  cout << "rvalue initialization:" << endl;
  auto p1 = make_unique1< Overload >(2); // rvalue
  cout << endl;

  cout << "lvalue initialization:" << endl;
  int i = 1;
  auto p2 = make_unique1< Overload >(i); // lvalue
  cout << endl;

  cout << "forwarder: " << endl;
  auto t = make_unique2< Forwarder >(2, i, 3);
  cout << endl;


  cout << "READY." << endl;
}
