/*
  C++11 - prefer task-based programming to thread-based (Meyers / item 35)


  A normal 'std::promise' prepares a oneshot communication and cannot be
  reused.

  The 'std::future' provides a mechanism for communication among threads, pass
  values or retrieve resulting values in an asynchronous operation.

  Shared futures share their state and TLS (thread local storage) among tasks
  or threads, respectively. Thus one future's value can be checked in several
  threads.


  In the example a promise provides a oneshot 'std::future' for passing a return
  value and for passing a barrier. Parallelism is implemented via 'std::async'.


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


#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

using namespace std;

// NOTE: if this is called 'accumulate(' a 'using namespace std;' will throw errors, std::accumulate or this function?
void do_accumulate(vector< int >::iterator first,
                vector< int >::iterator last,
                std::promise< int > accumulate_promise)
{
  cout << "CALLED: do_accumulate()" << endl;
  int sum = std::accumulate(first, last, 0);
  accumulate_promise.set_value(sum);  // notify future for return result
}

void do_work(std::promise< void > barrier)
{
  cout << "CALLED: do_work()" << endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  barrier.set_value(); // notify barrier
}

int main()
{
  // demonstrate using promise< int > to transmit a result between threads
  // promise -> future -> thread / async
  cout << "promise< int > " << endl;
  vector< int > numbers = { 1, 2, 3, 4, 5, 6 };
  std::promise< int > accumulate_promise;
  std::future< int > accumulate_future = accumulate_promise.get_future();
  std::thread work_thread(do_accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));
  accumulate_future.wait();  // wait for result
  auto res = accumulate_future.get(); // retrieving a result
  cout << "result = " << res << endl;
  work_thread.join();  // wait for thread completion
  cout << endl;

  // demonstrate using promise< void > to signal state between threads
  cout << "promise< void >" << endl;
  std::promise< void > barrier;
  std::future< void > barrier_future = barrier.get_future();
  std::thread new_work_thread(do_work, std::move(barrier));
  barrier_future.wait();
  new_work_thread.join();
  cout << endl;

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
