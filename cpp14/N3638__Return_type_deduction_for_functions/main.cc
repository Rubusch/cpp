/*
 * c++14: N3638 "Return type deduction for normal functions"
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

using namespace std;

template<class T>
auto square(T n)
{
  return n * n;
}

int main()
{
  int ires = square(3);
  cout << "square of 3 is " << ires << endl;

  double dres = square(1.4142);
  cout << "square of 1.4142 is " << dres << endl;

  /*
    further examples (TODO check)
    auto f(); // return type is unknown
    auto f() { return 42; } // return type is int
    auto f(); // redeclaration
    int  f(); // error, declares a different function
  */
  return 0;
}

