/*
 * c++14: N3649 "Generic (Polymorphic) Lambda Expressions (Revision 3)"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3649.html
 *
 * compiler support:
 * gcc 4.9 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>

using namespace std;

struct lambda1
{
  template<typename A, typename B>
  auto operator()(A a, B b) const -> decltype(a * b)
  {
    return a * b;
  }
};

int main()
{
  // not sure, if this refers to the specified proposal for C++14
  auto lambda = lambda1();
  cout << lambda(7, 3) << endl;

  // lambda
  auto product = [](auto a,auto b){return a * b;};
  cout << product(7, 3) << endl;
  return 0;
}

