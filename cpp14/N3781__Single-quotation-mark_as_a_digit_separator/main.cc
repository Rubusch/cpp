/*
 * c++14: N3781 "Single-quotation-mark as a digit separator"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3781.pdf
 *
 * compiler support:
 * gcc 4.9 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>

using namespace std;

int main()
{
  int x[3]; // cannot be auto

  x[1] = { 1'2'3 }; // wonderfull C++14

  cout << "x[1] = " << x[1] << endl;
}

