/*
  C++11 - use 'std::shared_ptr' for shared-ownership resource
  management (Meyers / item 19)

  'std::shared_ptr' may transfer ownership to other smartpointers,
  uses refcnt


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

  @author: Lothar Rubusch <L.Rubusch@gmail.com>
 */

#include <iostream>
#include <memory> /* shared_ptr */

using namespace std;

class Lemon
{
public:
  Lemon() = default;
  auto juice() const { return "Lemon Juice"; }
};


int main(void)
{
  // unique_ptr to shared_ptr
  cout << "create unique_ptr pUniqueLemon" << endl;
  std::unique_ptr< Lemon > pUniqueLemon(new Lemon());
  cout << "pUniqueLemon->juice(): " << pUniqueLemon->juice() << endl;

  std::shared_ptr< Lemon > pSharedLemon;
  if (nullptr == pSharedLemon) {
    cout << "pSharedLemon is null" << endl;
  }

  cout << "moving unique_ptr() to shared_ptr()" << endl;
  pSharedLemon = std::move(pUniqueLemon);
  cout << "pSharedLemon->juice(): " << pSharedLemon->juice() << endl;

  if (nullptr == pUniqueLemon) {
    cout << "pUniqueLemon is now null" << endl;
  }

  // ERROR! shared_ptr cannot be converted to unique_ptr
  //  std::unique_ptr< Lemon > pYetAnotherLemon;
  //  pYetAnotherLemon = std::move( pSharedLemon );

  cout << "READY." << endl;

  return EXIT_SUCCESS;
}
