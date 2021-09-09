/*
  futures


  The 'std::future' provides a mechanism for communication among
  threads, pass values or retrieve resulting values in an asynchronous
  operation.



  THEORY

  The three meanings of 'thread' in concurrent C++ software:

  * Hardware Threads: are the threads that actually perform
    computation.  Contemporary machine architectures offer one or more
    hardware threads per CPU core.

  * Software Threads: (also known as OS threads or system threads) are
    the threads that the operating system manages across all processes
    and schedules for execution on hardware threads. It's typically
    possible to create more software threads than hardware threads,
    because when a software thread is blocked (e.g. on I/O or waiting
    for a mutex or condition variable), throughput can be improved by
    executing other, unblocked threads.

  * std::threads are objects in a C++ process that act as handles to
    underlying software threads. Some 'std::thread' objects represent
    "null" handles, i.e., correspond to no software thread, because
    they're in a default-constructed state (hence have no function to
    execute), have been moved from (the moved-to 'std::thread' then
    acts as the handle to the underlying software thread), have been
    joined (the function they were to run has finished), or have been
    detached (the connection between them and their underlying
    software thread has been served).



  C++11 - be aware of varying thread handle destructor behavior
  (Meyers / item 38)

                             shared state
  +--------+               +----------------+                     +--------+
  | Caller |<--- future ---| Callee's State |<--- std::promise ---| Callee |
  +--------+               |   Result       |                     +--------+
                           +----------------+


  CONCLUSION

  * Future destructors normally just destroy the future's data
    members.

  * The final future referring to a shared state for a non-deferred
    task launched via 'std::async' blocks until the task completes.



  RESOURCES

  * Effective Modern C++, Scott Meyers, 2015

  * cppreference.com, 2019
 */

/*
#include <future>
#include <iostream>
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

#include <chrono> /* chrono::seconds for sleep */
#include <future>
#include <iostream>
#include <mutex>
#include <thread> /* thread, this_thread::sleep_for() */

using namespace std;

std::mutex mtx;

int doAsyncWork(string str)
{
  std::lock_guard< std::mutex > lock(mtx);
  int cnt = 0;
  for (cnt = 0; cnt < 3; ++cnt) {
    cout << str << " " << cnt << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
  return 0;
}


int main(void)
{
  cout << "future from a packaged task" << endl;
  // set up a packaged_task with a lambda, then obtain the future out of the
  // task
  std::packaged_task< int() > task([]() { return doAsyncWork("task"); });
  std::future< int > future_from_task = task.get_future();
  // move the task into a separate thread, to set it "join()" later
  std::thread thr(std::move(task));

  cout << "future from an async()" << endl;
  std::future< int > future_from_async =
      std::async(std::launch::async, []() { return doAsyncWork("async"); });

  // promise for one-shot async tasks
  cout << "future from a promise" << endl;
  std::promise< int > promi;
  std::future< int > future_from_promise = promi.get_future();
  std::thread([&promi]() {
    doAsyncWork("promise");
    promi.set_value_at_thread_exit(9);
  })
      .detach();


  cout << "waiting..." << endl << std::flush;
  future_from_task.wait();
  future_from_async.wait();
  future_from_promise.wait();

  // yield results
  auto res_from_task = future_from_task.get();
  auto res_from_async = future_from_async.get();
  auto res_from_promise = future_from_promise.get();

  cout << "result from task: " << res_from_task << endl;
  cout << "result from async: " << res_from_async << endl;
  cout << "result from promise: " << res_from_promise << endl;

  // join the first task's thread, this will actually start the thread
  thr.join(); // if this is missing: 'ERROR terminate called without an active
              // exception'

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
