/*
  C++11 - make 'const' member functions thread safe (Meyers / item 16)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - make 'const' member functions thread safe unless you're certain they'll
    never (!) be used in a concurrent context

  - use of 'std::atomic' variables may offer better performance than a mutex,
    but they're suited for manipulation of only a single variable or memory
    location

  - for a single variable or memory location requiring synchronization, use
    of a 'std::atomic' is adequate, but once you get to two or more variables
    or memory locations that require manipulations as a unit, you should
    reach for a mutex

  @author: Lothar Rubusch
  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <thread> /* thread, this_thread::sleep_for() */
#include <chrono> /* chrono::seconds */

using namespace std;


void itchy()
{
  for (int idx=0; idx<5; ++idx) {
    cout << "Bang!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
}

void scratchy(int counter)
{
  for (int idx=0; idx<counter; ++idx) {
    cout << "Pong!!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
  }
}


int main(void)
{
  cout << "start threads:" << endl;

  std::thread thread_itchy(itchy);
  std::thread thread_scratchy(scratchy, 3);

  // each should wait for the other
  thread_itchy.join();
  thread_scratchy.join();

  cout << "both completed!" << endl;

  cout << "READY." << endl;
  return 0;
}

