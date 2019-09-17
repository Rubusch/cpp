/*
  C++11 - prefer task-based programming to thread-based (Meyers / item 35)


  A normal 'std::promise' is a oneshot task and cannot be reused.


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

// using namespace std; // ERROR using std here, with call to thread()

void accumulate(std::vector< int >::iterator first,
                std::vector< int >::iterator last,
                std::promise< int > accumulate_promise)
{
  int sum = std::accumulate(first, last, 0);
  accumulate_promise.set_value(sum);  // Notify future
}

void do_work(std::promise< void > barrier)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier.set_value();
}

//using namespace std;
int main()
{
  // demonstrate using promise< int > to transmit a result between threads
  // promise -> future -> thread / async
  std::cout << "promise< int >: ";
  std::vector< int > numbers = { 1, 2, 3, 4, 5, 6 };
  std::promise< int > accumulate_promise;
  std::future< int > accumulate_future = accumulate_promise.get_future();
  std::thread work_thread(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));
  accumulate_future.wait();  // wait for result
  std::cout << "result = " << accumulate_future.get() << std::endl;
  work_thread.join();  // wait for thread completion

  using namespace std;

  // demonstrate using promise< void > to signal state between threads
  cout << "promise< void >" << endl;
  std::promise<void> barrier;
  std::future<void> barrier_future = barrier.get_future();
  std::thread new_work_thread(do_work, std::move(barrier));
  barrier_future.wait();
  new_work_thread.join();

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
