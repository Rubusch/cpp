/*
  C++11 - use 'std::shared_ptr' for shared-ownership resource management
  (Meyers / item 19)

  'std::shared_ptr' may transfer ownership to other smartpointers,
  uses refcnt

  this example demonstrates a shared_ptr with a customized deleter
  function e.g. to log deletion or do additional work at delete of the
  object, outside of the dtor


  IMPORTANT:

  - 'std::shared_ptr's are twice the size of a raw pointer!
  - memory for the reference count must be dynamically allocated!
  - increments and decrements of the reference count must be atomic!


  CONCLUSION:

  - 'std::shared_ptr's offer convenience approaching that of garbage
    collection for the shared lifetime management of arbitrary
    resources

  - compared to 'std::unique_ptr', 'std::shared_ptr' objects are
    typically twice as big, incur overhead for control blocks, and
    requre atomic reference count manipulation

  - default resource destruction is via 'delete', but custom deleters
    are supported; the type of the deleter has no effect on the type
    of the 'std::shared_ptr'

  - avoid creating 'std::shared_ptr's from variables of raw pointer
    type

  resources: Effective Modern C++, Scott Meyers, 2015

  @author: lothar Rubusch
 */

#include <iostream>
#include <memory> /* shared_ptr */

using namespace std;

class Lemon
{
public:
  Lemon() { cout << "CALLED: Lemon()" << endl; }
  ~Lemon() { cout << "CALLED: ~Lemon()" << endl; }
};


auto delete_lemon = [](Lemon *pl) {
  cout << "CALLED: external deleter for Lemon" << endl;
  delete pl;
};


int main(void)
{
  // unique_ptr to shared_ptr
  cout << "create unique_ptr pLemon" << endl;
  std::shared_ptr< Lemon > pLemon(new Lemon(), delete_lemon);
  cout << endl;

  cout << "pLemon->reset()" << endl;
  pLemon.reset();

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
