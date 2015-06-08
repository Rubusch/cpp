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

using namespace std;

template<class T>
auto square(T n)
{
  return n * n;
}

int main()
{
  /*
    the referred example provided by the document
    (just the wording changes and becomes more distinct)
  */
// TODO in case stress more on the particular change here    
  int x = 4;
  cout << "x was " << x << endl;

  cout << "the lambda expression Updates ::x to 6, and initializes y to 7." << endl;
  auto y = [&r = x, x = x+1]()->int {
    r += 2;
    return x+2;
  }();
  cout << "y is " << y << endl;

  return 0;
}

