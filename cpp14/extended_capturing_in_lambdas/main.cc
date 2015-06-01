/*
 * c++14: extended capturing in lambdas example
 *
 * compiler support
 *
 * Clang 3.4 (ref. as "Initialized lambda captures", N3648) TODO check    
 *
 * author: Lothar Rubusch
 */
#include <iostream>
#include <chrono> // system_clock

using namespace std;
using namespace chrono;

int main()
{

  /*
   * another change to lambdas involves capturing valirables,
   * in C++14, cpatured variables can have an initializing expression
   */
  auto timer = [val = system_clock::now()]{ return system_clock::now() - val; };
  auto diff = timer();
  // TODO check context for timer()
  cout << "some timer value: " << diff.count() << endl;
  return 0;
}
