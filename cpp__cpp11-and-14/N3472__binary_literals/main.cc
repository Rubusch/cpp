/*
 * c++14: N3472 "Binary literals"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3472.pdf
 *
 * compiler support:
 * gcc 4.3 (GNU)
 * Clang 2.9
 *
 * author: Lothar Rubusch
 */
#include <iostream>

using namespace std;

int main()
{
  int var = 0b1000; // binary literal

  cout << "variable: " << var << endl; // prints out '8' (decimal)
}
