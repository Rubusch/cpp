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
#include <thread> /* thread, this_thread::sleep_for() */
#include <future>
#include <chrono> /* chrono::seconds for sleep */

using namespace std;

void doAsyncWork()
{
  for (auto cnt=0; cnt<10; ++cnt) {
    cout << cnt << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
}


int main(void)
{
  // thread
  std::thread thr(doAsyncWork);

  // future, a task
  auto fut = std::async(doAsyncWork);

  cout << "TODO" << endl;

  cout << "READY." << endl;
  return 0;
}

