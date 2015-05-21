/*
 * c++14: extended capturing in lambdas example
 *
 * author: Lothar Rubusch
 */
#include <iostream>

using namespace std;

/*
  usage
*/
int main()
{
  /*
   * another change to lambdas involves capturing valirables,
   * in C++14, cpatured variables can have an initializing expression
   */
  auto timer = [val = system_clock::now()]{ return system_clock::now() - val; };

  timer();

  // TODO    

  return 0;
}
