/*
 * c++14: generic lambdas example
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

  auto lambda = lambda1();

  cout << lambda(7, 3) << endl;
  return 0;
}

