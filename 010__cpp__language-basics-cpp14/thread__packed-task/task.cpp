/*
  C++11 - prefer task-based programming to thread-based (Meyers / item 35)

  C++11 - specify 'std::launch::async' if asynchronicity is essential
          thread__async-launch-policies  (Meyers / item 36)



  The 'std::async' creates a task, that may be parallelized by the compiler to
  asynchronous threads.

  std::launch::async - start asynchronously

  std::launch::deferred - start later, at 'wait()'

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
#include <cmath>
#include <thread>
#include <future>
#include <functional>

using namespace std;


// unique function to avoid disambiguating the std::pow overload set
int func(int x, int y) { return std::pow(x,y); }


void task_lambda()
{
  // better replacement for a bind version, may be stricter on type checking
  // (or at least has some while bind may leave certain things open)
  cout << "lambda: setup task" << endl;
  std::packaged_task< int(int, int) > task( [](int a, int b) { return func(a, b); } );
  std::future< int > result = task.get_future();

  cout << "lambda: start task" << endl;
  task(3, 5);

  cout << "lambda:\t" << result.get() << '\n';
}

void task_bind()
{
  // bind approach is somehow the legacy approach for the lambda version
  cout << "bind: setup task" << endl;
  std::packaged_task< int() > task(std::bind(func, 3, 5));
  std::future< int > result = task.get_future();

  cout << "bind: start task" << endl;
  task();

  cout << "bind:\t" << result.get() << '\n';
}

void task_thread()
{
  // classic approach with most flexibility, the hand-made thread implementation
  cout << "thread: setup task" << endl;
  std::packaged_task<int(int,int)> task(func);
  std::future< int > result = task.get_future();

  cout << "thread: start task" << endl;
  std::thread task_td(std::move(task), 3, 5);
  task_td.join();

  cout << "task_thread:\t" << result.get() << '\n';
}


int main()
{
  cout << "compare lambda, bind and thread solution for a task generated via 'std::packaged_task'" << endl;
  task_lambda();

  task_bind();

  task_thread();

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}

