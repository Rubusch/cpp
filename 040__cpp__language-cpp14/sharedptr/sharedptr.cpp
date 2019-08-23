/*
  C++11 - use 'std::shared_ptr' for shared-ownership resource management (Meyers / item 19)

  'std::shared_ptr' may transfer ownership to other smartpointers; uses refcnt

  demonstrates operations with 'std::shared_ptr'


  CONCLUSION:

  - 'std::shared_ptr's offer convenience approaching that of garbage collection
    for the shared lifetime management of arbitrary resources

  - compared to 'std::unique_ptr', 'std::shared_ptr' objects are typically twice
    as big, incur overhead for control blocks, and requre atomic reference count
    manipulation

  - default resource destruction is via 'delete', but custom deleters are
    supported; the type of the deleter has no effect on the type of the
    'std::shared_ptr'

  - avoid creating 'std::shared_ptr's from variables of raw pointer type

  - 'std::shared_ptr' does not have an operator[] (C++11)

  - a 'std::shared_ptr' to a raw array is almost always a sign of bad design

  - never mix an array of 'std::shared_ptr's with raw pointers

  resources: Effective Modern C++, Scott Meyers, 2015

  @author: lothar Rubusch
 */

#include <iostream>
#include <memory> /* shared_ptr */

using namespace std;


class Box
{
private:
  int number_of_toys;

public:
  Box( int number) : number_of_toys(number)
  {
    cout << "CALLED: Box(" << number << ")" << endl;
  }
  ~Box()
  {
    cout << "CALLED: ~Box()" << endl;
  }

  auto box_content() const
  {
    return number_of_toys;
  }
};



int main(void)
{
  // creating a pointer and initialization
  std::shared_ptr< Box > pBox( new Box(12) );

  // creation of an empty pointer is possible
  std::shared_ptr< Box > pAnotherBox;

  // check if a pointer is empty
  if (!pAnotherBox) {
    cout << "there is no pAnotherBox content" << endl;
  }

  // check if a pointer is empty
  auto content = pBox->box_content();
  cout << "the pBox contains " << content << " toys" << endl;

  // copyable
  std::shared_ptr< Box > pCopyBox = pBox;
  cout << "copy of pBox, pCopyBox: " << pCopyBox->box_content() << endl;

  // BUT: moveable
  cout << "move of pBox to pAnotherBox" << endl;
  pAnotherBox = std::move(pBox);

  // the moving pointer is now obsolete
  if (nullptr == pBox) {
    cout << "the pBox disappeared...." << endl;
  }
  cout << "the moved pAnotherBox contains " << pAnotherBox->box_content() << " toys" << endl;

  // reset a unique_ptr
  cout << "trash pAnotherBox" << endl;
  pAnotherBox.reset();

  // creating (must point to dynamic memory)..
  auto val = 123;
  cout << "create another pointer pInt with " << val << endl;
  std::shared_ptr< int > pInt = std::make_shared< int >( val );

  // get (shred_ptr) corresponds to release (unique_ptr)
  // pass the pointee to a raw pointer
  auto *pVal = pInt.get();
  cout << "yet another smartpointer, the raw pointer '*pVal' shows: " << *pVal << endl;


  cout << "READY." << endl;

  return EXIT_SUCCESS;
}
