/*
 * c++14: extended capturing in lambdas example
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
  timer();

  // TODO no fancy output, is there a easy way to make it nicer?    
  return 0;
}
