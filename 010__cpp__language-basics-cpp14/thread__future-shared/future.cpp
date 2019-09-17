/*
  C++11 - prefer task-based programming to thread-based (Meyers / item 35)


  The example shows signaling a kickoff to two threads and measure their
  execution time.

  The example uses chrono, promise, futures and async.


  The class template std::shared_future provides a mechanism to access the
  result of asynchronous operations, similar to std::future, except that
  multiple threads are allowed to wait for the same shared state. Unlike
  std::future, which is only moveable (so only one instance can refer to any
  particular asynchronous result), std::shared_future is copyable and multiple
  shared future objects may refer to the same shared state.

  Access to the same shared state from multiple threads is safe if each thread
  does it through its own copy of a shared_future object.



  THEORY

  The three meanings of 'thread' in concurrent C++ software:

  * Hardware Threads: are the threads that actually perform computation.
    Contemporary machine architectures offer one or more hardware threads per
    CPU core.

  * Software Threads: (also known as OS threads or system threads) are the
    threads that the operating system manages across all processes and schedules
    for execution on hardware threads. It's typically possible to create more
    software threads than hardware threads, because when a software thread is
    blocked (e.g. on I/O or waiting for a mutex or condition variable),
    throughput can be improved by executing other, unblocked threads.

  * std::threads are objects in a C++ process that act as handles to underlying
    software threads. Some 'std::thread' objects represent "null" handles, i.e.,
    correspond to no software thread, because they're in a default-constructed
    state (hence have no function to execute), have been moved from (the
    moved-to 'std::thread' then acts as the handle to the underlying software
    thread), have been joined (the function they were to run has finished), or
    have been detached (the connection between them and their underlying
    software thread has been severed).



  CONCLUSION

  * The 'std::thread' API offers no direct way to get return values from
    asynchronously run functions, and if those functions throw, the program is
    terminated.

  * Thread-based programming calls for manual management of thread exhaustion,
    oversubscription, load balancing, and adaptation to new platforms.

  * Task-based programming via 'std::async' with the default launch policy
    handles most of these issues for you.



  RESOURCES

  * Effective Modern C++, Scott Meyers, 2015

  * cppreference.com, 2019
 */

#include <iostream>
#include <future>
#include <chrono>

using namespace std;


int main()
{
  // oneshot command 'start' to threads via 'std::promise' (promise -> oneshot command)
  std::promise< void > ready_promise;
  std::shared_future< void > ready_future(ready_promise.get_future());

  // receivers for oneshot command 'start'
  std::promise< void > t1_ready_promise;
  std::promise< void > t2_ready_promise;


  // time measuring
  std::chrono::time_point< std::chrono::high_resolution_clock > start;

  // initializing a function pointer
  auto func1 = [&, ready_future]() -> std::chrono::duration< double, std::milli >
  {
   t1_ready_promise.set_value();
   ready_future.wait(); // waits for the signal from main()
   return std::chrono::high_resolution_clock::now() - start;
  };

  // initializing another function pointer
  auto func2 = [&, ready_future]() -> std::chrono::duration< double, std::milli >
  {
   t2_ready_promise.set_value();
   ready_future.wait(); // waits for the signal from main()
   return std::chrono::high_resolution_clock::now() - start;
  };

  auto future1 = t1_ready_promise.get_future();
  auto future2 = t2_ready_promise.get_future();

  auto result1 = std::async(std::launch::async, func1);
  auto result2 = std::async(std::launch::async, func2);

  // wait for the threads to become ready
  future1.wait();
  future2.wait();

  // the threads are ready, start the clock
  start = std::chrono::high_resolution_clock::now();

  // signal the threads to go
  ready_promise.set_value();

  cout << "Thread 1 received the signal "
       << result1.get().count() << " ms after start\n"
       << "Thread 2 received the signal "
       << result2.get().count() << " ms after start\n";

  cout << "TODO" << endl;        

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}

