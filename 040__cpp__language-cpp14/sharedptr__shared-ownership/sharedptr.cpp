/*
  C++11 - use 'std::shared_ptr' for shared-ownership resource management (Meyers / item 19)

  'std::shared_ptr' may transfer ownership to other smartpointers, uses refcnt

  conclusion:

  - 'std::shared_ptr's offer convenience approaching that of garbage collection
    for the shared lifetime management of arbitrary resources

  - compared to 'std::unique_ptr', 'std::shared_ptr' objects are typically twice
    as big, incur overhead for control blocks, and requre atomic reference count
    manipulation

  - default resource destruction is via 'delete', but custom deleters are
    supported; the type of the deleter has no effect on the type of the
    'std::shared_ptr'

  - avoid creating 'std::shared_ptr's from variables of raw pointer type

  @author: lothar Rubusch
 */

#include <iostream>
#include <memory> /* shared_ptr */

using namespace std;


int main(void)
{
// TODO

  cout << "READY." << endl;

  return EXIT_SUCCESS;
}
