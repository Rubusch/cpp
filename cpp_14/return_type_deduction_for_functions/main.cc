/*
 * c++14: return type deduction for functions example
 *
 * author: Lothar Rubusch
 */
#include <iostream>

using namespace std;

auto square(int n)
{
  return n * n;
}

int main()
{
  int ires = square(3);
  cout << "square of 3 is " << ires << endl;

  // TODO interesting, a float type provided, int returned?!    
  double dres = square(1.4142);
  cout << "square of 1.4142 is " << dres << endl;

  return 0;
}

