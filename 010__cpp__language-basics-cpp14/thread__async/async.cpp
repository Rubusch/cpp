/*
  C++11 - prefer task-based programming to thread-based (Meyers / item 35)



  The 'std::async' creates a task, that may be parallelized by the compiler to
  asynchronous threads.

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
#include <vector>
#include <future> /* std::async() */
#include <chrono> /* system_clock::now(), chrono::duration< double > */
#include <cassert> /* assert() */

using namespace std;


vector< unsigned long > checkPrimes(unsigned long num)
{
  vector< unsigned long > primes = { 2 };
  for (unsigned long idx=3; idx<num; ++idx) {
    bool isPrime = true;
    for (auto item : primes) {
      if (0 == idx % item) {
        isPrime = false;
        break;
      }
    }

    if (isPrime) {
      primes.push_back(idx);
    }
  }

  return primes;
}


int main()
{
  vector< unsigned long > asyncVec, vec;
  auto limit = 1000000;

  // async approach (launch-policy: async)
  {
    auto start = chrono::system_clock::now();
    auto handle = std::async(std::launch::async, checkPrimes, limit);
    auto stop = chrono::system_clock::now();
    // yield the result
    asyncVec = handle.get();
    chrono::duration< double > diff = stop - start;
    cout << "diff (std::async): " << diff.count() << " secs" << endl;
    cout << endl;
  }


  // iterative approach (way slower!)
  {
    auto start = chrono::system_clock::now();
    vec = checkPrimes(limit);
    auto stop = chrono::system_clock::now();
    // check via assert, that the result matches
    for (unsigned long idx=0; idx < vec.size(); ++idx) assert(vec[idx] == asyncVec[idx]);
    chrono::duration< double > diff = stop - start;
    cout << "diff (iterative): " << diff.count() << " secs"  << endl;
    cout << endl;
  }

/*
  // printer of the resulting primes
  cout << "result of the algorithm: " << endl;
  for (auto item : vec) cout << item << ' ';
  cout << endl << endl;
// */

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}

