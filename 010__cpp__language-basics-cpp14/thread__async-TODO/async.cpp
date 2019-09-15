/*
  C++11 - prefer task-based programming to thread-based (Meyers / item 35)

  runs a function asynchronously (potentially in a new thread) and returns a
  std::future that will hold the result

  The template function async runs the function f asynchronously (potentially in
  a separate thread which may be part of a thread pool) and returns a
  std::future that will eventually hold the result of that function call.



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
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>

std::mutex m;

struct X {
  void foo(int i, const std::string& str) {
    std::lock_guard<std::mutex> lk(m);
    std::cout << str << ' ' << i << '\n';
  }
  void bar(const std::string& str) {
    std::lock_guard<std::mutex> lk(m);
    std::cout << str << '\n';
  }
  int operator()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        return i + 10;
    }
};


template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
  auto len = end - beg;
  if (len < 1000)
    return std::accumulate(beg, end, 0);

  RandomIt mid = beg + len/2;
  auto handle = std::async(std::launch::async,
                             parallel_sum<RandomIt>, mid, end);
  int sum = parallel_sum(beg, mid);
  return sum + handle.get();
}


int main()
{
  std::vector<int> v(10000, 1);
  std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';

  X x;
  // Calls (&x)->foo(42, "Hello") with default policy:
  // may print "Hello 42" concurrently or defer execution
  auto a1 = std::async(&X::foo, &x, 42, "Hello");
  // Calls x.bar("world!") with deferred policy
  // prints "world!" when a2.get() or a2.wait() is called
  auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
  // Calls X()(43); with async policy
  // prints "43" concurrently
  auto a3 = std::async(std::launch::async, X(), 43);
  a2.wait();                     // prints "world!"
  std::cout << a3.get() << '\n'; // prints "53"
  // if a1 is not done at this point, destructor of a1 prints "Hello 42" here

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}

