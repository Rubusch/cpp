/*
  C++11 - specify 'std::launch::async' if asynchronicity is essential
  (Meyers / item 36)



  The 'std::async' creates a task, that may be parallelized by the compiler to
  asynchronous threads.

  The template function async runs the function f asynchronously (potentially in
  a separate thread which may be part of a thread pool) and returns a
  std::future that will eventually hold the result of that function call.

  The implementation may extend the behavior of the first overload of std::async
  by enabling additional (implementation-defined) bits in the default launch
  policy.

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
#include <iostream>
#include <future>
#include <mutex>

using namespace std;


std::mutex mtx;

class Fruit {
public:
  void lemon(int idx, const std::string& str) {
    std::lock_guard< std::mutex > lock(mtx);
    cout << "CALLED: Fruit::lemon() " << str << ' ' << idx << endl;
  }

  void orange(const std::string& str) {
    std::lock_guard< std::mutex > lock(mtx);
    cout << "CALLED: Fruit::orange() " << str << endl;
  }

  int operator()(int idx) {
    std::lock_guard< std::mutex > lock(mtx);
    cout << "CALLED: Fruit::operator() " << idx << endl;
    return idx + 10;
  }
};


int main()
{
  Fruit fresh_fruit;
  // calls (&x)->lemon(42, "Hello") with default policy:
  //   may print "Hello 42" concurrently or defer execution
  auto a1 = std::async(&Fruit::lemon, &fresh_fruit, 42, "sour");

  // calls x.bar("world!") with deferred policy
  // prints "world!" when a2.get() or a2.wait() is called
  auto a2 = std::async(std::launch::deferred, &Fruit::orange, fresh_fruit, "sweet");

  // calls X()(43); with async policy
  // prints "43" concurrently
  auto a3 = std::async(std::launch::async, Fruit(), 43);

  a2.wait();                     // prints "world!"
  cout << a3.get() << endl;      // prints "53"

  // if a1 is not done at this point, destructor of a1 prints "Hello 42" here


  cout << "READY." << endl;
  return EXIT_SUCCESS;
}

