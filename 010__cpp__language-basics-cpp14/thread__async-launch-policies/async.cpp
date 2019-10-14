/*
  C++11 - specify 'std::launch::async' if asynchronicity is essential
  (Meyers / item 36)



  The 'std::async' creates a task, that may be parallelized by the compiler to
  asynchronous threads.

  It may start right away (std::launch::async) or its start may be deferred
  (std::launch::deferred), triggered at a call to 'wait()' or get results.

  The template function async runs the function f asynchronously (potentially in
  a separate thread which may be part of a thread pool) and returns a
  std::future that will eventually hold the result of that function call.

  The implementation may extend the behavior of the first overload of std::async
  by enabling additional (implementation-defined) bits in the default launch
  policy.



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

  * The default launch policy for 'std::async' permits both asynchronous and
    synchronous task execution.

  * This flexibility leads to uncertainty when accessing 'thread_locals' (TLS,
    Thread Local Storage), implies that the task may never execute, and affects
    program logic for timeout-based wait calls.

  * Specify 'std::launch::async' if asynchronous task execution is essential.



  RESOURCES

  * Effective Modern C++, Scott Meyers, 2015

  * cppreference.com, 2019

 */
#include <chrono> /* chrono::seconds */
#include <future>
#include <iostream>
#include <mutex>

using namespace std;


std::mutex mtx; // needed to lock while thread execution

class FruitBox
{
public:
  void lemon(const std::string &str, int num)
  {
    std::lock_guard< std::mutex > lock(mtx);
    for (auto idx = 0; idx < num; ++idx) {
      cout << "LEMON (" << str << ")" << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
  }

  void orange(const std::string &str, int num)
  {
    std::lock_guard< std::mutex > lock(mtx);
    for (auto idx = 0; idx < num; ++idx) {
      cout << "ORANGE (" << str << ")" << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
  }

  int operator()(int num)
  {
    std::lock_guard< std::mutex > lock(mtx);
    for (auto idx = 0; idx < num; ++idx) {
      cout << "FRUITBOX (async)" << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
    return num + 1;
  }
};


int main()
{
  FruitBox fresh_fruit;

  auto idx = 0;
  do {
    // calls '(&fresh_fruit)->lemon("unspecified", idx);'
    // with default policy, may print concurrently or defer execution
    auto a1 = std::async(&FruitBox::lemon, &fresh_fruit, "unspecified", idx);

    // calls 'fresh_fruit.orange("deferred", idx);'
    // with deferred policy (later)
    auto a2 = std::async(std::launch::deferred, &FruitBox::orange, fresh_fruit,
                         "deferred", idx);

    // calls 'FruitBox()(idx);'
    // with async policy
    auto a3 = std::async(std::launch::async, FruitBox(), idx);

    a2.wait();      // now starts a2 threads
    idx = a3.get(); // a3 yields incremented idx

    // if a1 is not done at this point, destructor of a1 prints "LEMON" here
  } while (idx < 5);

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
