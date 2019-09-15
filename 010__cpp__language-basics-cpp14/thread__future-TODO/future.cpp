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

int doAsyncWork()
{
  for (auto cnt=0; cnt<10; ++cnt) {
    cout << cnt << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
  return 0;
}


int main(void)
{
  cout << "future from a packaged task" << endl;
//*
  std::packaged_task< int() > task( [](){ return 7; } );
/*/
  // FIXME
  std::packaged_task< void() > task( [](){ doAsyncWork(); } );
// */
  std::future< int > future_from_task = task.get_future();
  std::thread thr( std::move(task) );
  cout << endl;

  cout << "future from an async()" << endl;
//*
  std::future< int > future_from_async = std::async( std::launch::async, [](){ return 8; } );
/*/
  // FIXME
  std::future< void > future_from_async = std::async( std::launch::async, [](){ doAsyncWork(); } );
// */
  cout << endl;

  cout << "future from a promise" << endl;
  std::promise< int > promi;
  std::future< int > future_from_promise = promi.get_future();
  std::thread( [&promi](){ promi.set_value_at_thread_exit(9); } ).detach();
  cout << endl;


  cout << "waiting..." << endl << std::flush;
  future_from_task.wait();
  future_from_async.wait();
  future_from_promise.wait();

  // future, a task
//  auto fut = std::async(doAsyncWork);
//  cout << "TODO" << endl;

  cout << "Yield results: " << future_from_task.get() << ' '
       << future_from_async.get() << ' '
       << future_from_promise.get() << endl;

  thr.join(); // ERROR if this is missing: 'terminate called without an active exception'

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}

