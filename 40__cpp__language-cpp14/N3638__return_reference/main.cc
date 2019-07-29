/*
 * c++14: N3638 "Return type deduction for normal functions"
 *
 * "Normally, decltype produces the type you expect."
 * Scott Meyers, Effective Modern C++, 2015, p.29
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3638.html
 *
 * compiler support:
 * gcc 4.8/4.9 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>

/*
  for lvalue expressions of type T other than names, decltype always reports a
  type of T&
 */
decltype(auto) func1()
{
  int x = 777;
  return x; // decltype(x) is int, func1 returns int
}

decltype(auto) func2()
{
  int x = 777;
  return (x); // decltype( (x) ) is int&, func2 returns int&
}


using namespace std;

int main()
{
  cout << "CAUTION at decltype return deduction and braces!" << endl;

  cout << "func1() returns int: "  << func1() << endl;
  cout << "func2() returns int&: " << &func2() << endl;
  cout << endl;

  return 0;
}

