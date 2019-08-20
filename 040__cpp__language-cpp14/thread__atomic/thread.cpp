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
#include <atomic> /* atomic */

using namespace std;


class Box
{
private:
  mutable std::atomic< bool > is_hit{ false }; // single small resource - ATOMIC!

public:
  void animal(const int sleep, const string name) const // const member function - CAUTION: race condition!!!
  {
    for (int idx=0; idx<3; ++idx) {
      this_thread::sleep_for(chrono::seconds(sleep));
      cout << "Bang! " << name << " is " << (is_hit?"":"not") << " hit" << endl;
      is_hit = (is_hit?false:true);
    }
  }
};



int main(void)
{
  cout << "start threads:" << endl;

  Box *pb = new Box();

  // thread (syntax!!)
  std::thread thread_itchy(&Box::animal, pb, 2, "itchy");
  std::thread thread_scratchy(&Box::animal, pb, 3, "scratchy");

  // each should wait for the other
  thread_itchy.join();
  thread_scratchy.join();

  cout << "both completed!" << endl;

  delete pb; pb = nullptr;

  cout << "READY." << endl;
  return 0;
}
