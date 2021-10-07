/*
  C++11 - prefer 'std::make_unique()' and 'std::make_shared()' to
  direct use of 'new' (Meyers / item 21)

  demonstrates operations with 'std::make_shared()'


  CONCLUSION:

  - compared to direct use of 'new', 'make' functions eliminate source
    code duplication, improve exception safety, and, for
    'std::make_shared()' and 'std::allocate_shared()', generate code
    that's smaller and faster

  - situations where use of 'make' functions is inappropriate include
    the need to specify custom deleters and a desire to pass braced
    initializers

  - for 'std::shared_ptr's, additional situations where 'make'
    functions may be ill-advised include (1) classes with custom
    memory management and (2) systems with memory concerns, very large
    objects, and 'std::weak_ptr's that outlive the corresponding
    'std::shared_ptrs'

  resources: Effective Modern C++, Scott Meyers, 2015

  @author: Lothar Rubusch <l.rubusch@gmail.com>
 */

#include <iostream>
#include <memory> /* shared_ptr */

using namespace std;


class Box
{
private:
  int number_of_toys;

public:
  Box(int number) : number_of_toys(number)
  {
    cout << "CALLED: Box(" << number << ")" << endl;
  }
  ~Box() { cout << "CALLED: ~Box()" << endl; }

  auto box_content() const { return number_of_toys; }
};


int main(void)
{
  // creating a pointer and initialization
  // template type: 'Box'; constructor argumten: '12' passed as argument to
  // 'std::make_shared(arg)'
  auto pBox = make_shared< Box >(12); // MAKE determines the type of pBox!!!


  // check if a pointer is empty
  auto content = pBox->box_content();
  cout << "the pBox contains " << content << " toys" << endl;

  // copyable
  // std::shared_ptr< Box > pCopyBox = pBox;
  auto pCopyBox = pBox;
  cout << "copy of pBox, pCopyBox: " << pCopyBox->box_content() << endl;

  // BUT: moveable
  cout << "move of pBox to pAnotherBox" << endl;
  auto pAnotherBox = std::move(pBox);

  // the moving pointer is now obsolete
  if (nullptr == pBox) {
    cout << "the pBox disappeared...." << endl;
  }
  cout << "the moved pAnotherBox contains " << pAnotherBox->box_content()
       << " toys" << endl;

  // reset a unique_ptr
  cout << "trash pAnotherBox" << endl;
  pAnotherBox.reset();

  // creating (must point to dynamic memory)..
  auto val = 123;
  cout << "create another pointer pInt with " << val << endl;
  auto pInt = std::make_shared< int >(val);

  // get (shred_ptr) corresponds to release (unique_ptr)
  // pass the pointee to a raw pointer
  auto *pVal = pInt.get();
  cout << "yet another smartpointer, the raw pointer '*pVal' shows: " << *pVal
       << endl;

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
