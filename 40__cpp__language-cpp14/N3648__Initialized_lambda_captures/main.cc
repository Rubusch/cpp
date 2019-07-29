/*
 * c++14: N3648 "Wording Changes for Generalized Lambda-capture"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3648.html
 *
 * compiler support:
 * gcc 4.9 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>
#include <chrono> // system_clock

using namespace std;
using namespace chrono;

template<class T>
auto square(T n)
{
  return n * n;
}

int main()
{
  //*
  // spec example
  int x = 4; cout << "x was " << x << endl;
  cout << "the lambda expression updates ::x to 6, and initializes y to 7." << endl;
  auto y = [&r = x, x = x+1]()->int {
    r += 2;
    return x+2;
  }();
  cout << "y is " << y << endl;
  //*/

  /*
   * another change to lambdas involves capturing variables,
   * in C++14, cpatured variables can have an initializing expression
   */
  auto timer = [val = system_clock::now()]{ return system_clock::now() - val; };
  auto diff = timer();
  cout << "some timer value: " << diff.count() << endl;

  return 0;
}

