/*
  C++11 - prefer task-based programming to thread-based (Meyers / item 35)



  runs a function asynchronously (potentially in a new thread) and returns a
  std::future that will hold the result

  The template function async runs the function f asynchronously (potentially in
  a separate thread which may be part of a thread pool) and returns a
  std::future that will eventually hold the result of that function call.

  The implementation may extend the behavior of the first overload of std::async
  by enabling additional (implementation-defined) bits in the default launch
  policy.



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
#include <chrono> /* system_clock::now(), chrono::duration< double > */
#include <cassert>

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



/*
std::mutex mtx;

struct Fruit {
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
// */



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

// TODO
/*
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
// */

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}

