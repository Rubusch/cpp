/*
  C++11 - prefer task-based programming to thread-based (Meyers / item 35)

// TODO                     

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

/*
#include <iostream>
#include <future>
#include <thread>

int main()
{
  // future from a packaged_task
  std::packaged_task<int()> task([]{ return 7; }); // wrap the function
  std::future<int> f1 = task.get_future();  // get a future
  std::thread t(std::move(task)); // launch on a thread

  // future from an async()
  std::future<int> f2 = std::async(std::launch::async, []{ return 8; });

  // future from a promise
  std::promise<int> p;
  std::future<int> f3 = p.get_future();
  std::thread( [&p]{ p.set_value_at_thread_exit(9); }).detach();

  cout << "Waiting..." << std::flush;
  f1.wait();
  f2.wait();
  f3.wait();
  cout << "Done!\nResults are: "
       << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
  t.join();
}
// */

#include <iostream>
#include <thread> /* thread, this_thread::sleep_for() */
#include <future>
#include <chrono> /* chrono::seconds for sleep */

using namespace std;

int doAsyncWork()
{
  int cnt=0;
  for (cnt=0; cnt<10; ++cnt) {
    cout << cnt << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
  return cnt;
}


int main(void)
{
  cout << "future from a packaged task" << endl;
  // set up a packaged_task with a lambda, then obtain the future out of the task
  std::packaged_task< int() > task( [](){ return doAsyncWork(); } );
  std::future< int > future_from_task = task.get_future();
  // move the task into a separate thread, to set it "join()" later
  std::thread thr( std::move(task) );
  cout << endl;

  cout << "future from an async()" << endl;
  std::future< int > future_from_async = std::async( std::launch::async, [](){ return doAsyncWork(); } );
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

  // join the first task's thread, this will actually start the thread
  thr.join(); // if this is missing: 'ERROR terminate called without an active exception'

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}

