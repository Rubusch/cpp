/*
  C++11 - make 'const' member functions thread safe (Meyers / item 16)
  C++11 - make 'std::threads' unjoinable on all paths (Meyers / item 37)



  RAII (resource acquisition is initialization)

  Any time you want to perform some action along every path out of a block, the
  normal approach is to put that action in the destructor of a local object.
  Such objects are known as RAII objects, and the classes they come from are
  known as RAII classes. (RAII itself stands for Resource Acquisition Is
  Initialization, although the crux of the technique is descruction, not
  initialization.) RAII classes are common in the Standard Library.



  CONCLUSION

  * Make 'const' member functions thread safe unless you're certain they'll
    never (!) be used in a concurrent context.

  * Use of 'std::atomic' variables may offer better performance than a mutex,
    but they're suited for manipulation of only a single variable or memory
    location.

  * For a single variable or memory location requiring synchronization, use
    of a 'std::atomic' is adequate, but once you get to two or more variables
    or memory locations that require manipulations as a unit, you should
    reach for a mutex.

  * Make 'std::threads' unjoinable on all paths.

  * Join-on-destruction can lead to difficult-to-debug performance anomalies

  * Detach-on-destruction can lead to difficult-to-debug undefined behavior

  * Delcare 'std::thread' objects last in lists of data members.



  RESOURCES

  * Effective Modern C++, Scott Meyers, 2015

  * cppreference.com
 */

#include <iostream>
#include <thread> /* thread, this_thread::sleep_for() */
#include <chrono> /* chrono::seconds */

using namespace std;


void itchy()
{
  for (int idx=0; idx<5; ++idx) {
    cout << "Bang!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
  }
}

void scratchy(int counter)
{
  for (int idx=0; idx<counter; ++idx) {
    cout << "Pong!!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
  }
}


int main(void)
{
  cout << "start threads:" << endl;

  std::thread thread_itchy(itchy);
  std::thread thread_scratchy(scratchy, 3);

  // each should wait for the other
  thread_itchy.join();
  thread_scratchy.join();

  cout << "both completed!" << endl;

  cout << "READY." << endl;
  return 0;
}
