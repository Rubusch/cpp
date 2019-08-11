/*
  C++11 - decltype (Meyers / item 3)

  template< typename T >
  void func(ParmType param);

  func(expr)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)

  T         - template type

  ParamType - parameter type, basically the template type with certain
              adornments, e.g. const, reference, pointer, etc.

  expr      - expression type, the deducted type from the ParamType in the
              expression


  conclusion:

  - decltype almost always yields the type of a variable or expression without
    any modifications

  - for lvalue expressions of type T other than names, decltype always reports a
    type of T&

  - C++14 supports decltype(auto), which, like auto, deduces a type from its
    initializer, but it performs the type deduction using the decltype rules

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <type_traits>  /* is_const:: */

#include <memory>
#include <utility> /* forward() */

using namespace std;

/*
// final cpp14 version
template< typename Con, typename Idx >
decltype(auto)
authAndAccess(Con&& con, Idx idx)
{
  cout << "authAndAccess()" << endl;
  return std::forward< Con >(con)[idx];
}
// */

class Box
{
  public:
  Box() { cout << "CALLED: ctor of Box" << endl; }
};




// final cpp11 version
template< typename Con, typename Idx >
auto
authAndAccess(Con&& con, Idx idx)
  -> decltype(std::forward< Con >(con)[idx])
{
  cout << "authAndAccess()" << endl;
  return std::forward< Con >(con)[idx];
}


int main(void)
{
  // TODO
  Box box;
  int index=0;

  auto obj = authAndAccess(box, index);
/*
  if (std::is_const< decltype(obj) >::value) {
    cout << "const" << endl;
  } else {
    cout << "not const" << endl;
  }
  cout << endl;

// small changes and effects in cpp11
decltype(auto) f1()
{
  int x=0;
// ...
  return x; // decltype(x) is int
}


decltype(auto) f1()
{
  int x=0;
// ...
  return (x); // decltype(x) is int&
}


// */
  cout << "READY." << endl;
}

