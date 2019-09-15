/*
  C++11 - prefer task-based programming to thread-based (Meyers / item 35)



  CONCLUSION

  * The 'std::thread' API offers no direct way to get return values from
    asynchronously run functions, and if those functions throw, the program is
    terminated.

  * Thread-based programming calls for manual management of thread exhaustion,
    oversubscription, load balancing, and adaptation to new platforms.

  * Task-based programming via 'std::async' with the default launch policy
    handles most of these issues for you.

  resources: Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */

#include <iostream>

using namespace std;


int main(void)
{
  // TODO

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}

