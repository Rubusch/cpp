/*
 * c++14: N3653 "Member initializers and aggregates"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3653.html
 *
 * compiler support:
 * gcc 5 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
  struct S { int a; const char* b; int c; int d = b[a]; };
  S ss = { 1, "asdf" };

  cout << "ss.a = " << ss.a << " [1], ss.b = \"" << ss.b << "\" [\"asdf\"], ss.c = " << ss.c << " [0], ss.d = '" << static_cast<char>(ss.d) << "' ['s']" << endl;
  cout << endl;

  /*
    the braced initializer,i.e. '{' and '}', represents "auto type deduction" via
    std::initializer_list<T>(arg); for the rest "auto type deduction" behaves as
    "template type deduction" (item 1 and 2, Meyers 2015)

    IMPORTANT:
    auto x = {1, 2, 3.0}; // may fail due to the different types, or provide a
    reasonable type for deduction of T

    func({1,2,3}); may fail also, if no explicit std::initializer_list<T>() with
    valid T was set explicitly

    auto a = {7}; does not init a single variable, but an array with one element!

    only declare std::initializer_list<T>() only when you have to!
   */
  struct X { int i, j, k = 42; };
  X a[] = { 1, 2, 3, 4, 5, 6 };
  X b[2] = { { 1, 2, 3 }, { 4, 5, 6 } };
  cout << "a[0].i = " << a[0].i << ", a[0].j = " << a[0].j << ", a[0].k = " << a[0].k << ", a[1].i = " << a[1].i << ", a[1].j = " << a[1].j << ", b[1].k = " << a[1].k << endl;
  cout << "b[0].i = " << b[0].i << ", b[0].j = " << b[0].j << ", b[0].k = " << b[0].k << ", b[1].i = " << b[1].i << ", b[1].j = " << b[1].j << ", b[1].k = " << b[1].k << endl;

  cout << "a == b; OK!" << endl;
}

