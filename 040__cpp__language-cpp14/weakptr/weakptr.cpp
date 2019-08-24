/*
  C++11 - use 'std::weak_ptr' for 'std::shared_ptr' like pointers that can dangle
  (Meyers / item 20)

  // TODO

  resource: Effective Modern C++, Scott Meyers, 2015

  'std::shared_ptr' is a typical implementation of 'std::weak_ptr'
  - a pointer to the control block; and
  - the stored pointer of the shared_ptr it was constructed from

  resource: cppreference.com

 @author: lothar Rubusch
 */

#include <iostream>
#include <memory> /* weak_ptr */

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
  cout << "create 'std::shared_ptr' pBox" << endl;
  std::shared_ptr< Box > pBox( new Box(12) );

  // creation of an empty pointer is possible
  cout << "create empty 'std::weak_ptr' pAnotherBox" << endl;
  std::weak_ptr< Box > pAnotherBox;

  cout << "assign pBox to pAnotherBox" << endl;
  pAnotherBox = pBox;

  // check if a pointer is empty
  cout << "now reset shared_ptr pBox" << endl;
  pBox.reset();
  if (!pBox) cout << "WARNING: pBox has no content" << endl;
  else  cout << "FAILED" << endl;

/*
  // check if a pointer is empty
  auto content = pAnotherBox->box_content();
  cout << "the pAnotherBox contains " << content << " toys" << endl;

  // copyable
  std::weak_ptr< Box > pCopyBox = pBox;
  cout << "copy of pBox, pCopyBox: " << pCopyBox->box_content() << endl;

  // BUT: moveable
  pAnotherBox = std::move(pBox);

  // the moving pointer is now obsolete
  if (nullptr == pBox) {
    cout << "the pBox disappeared...." << endl;
  }
  cout << "the moved pAnotherBox contains " << pAnotherBox->box_content() << " toys" << endl;

  // reset a weak_ptr
  cout << "trash the pAnotherBox" << endl;
  pAnotherBox.reset();

  // creating (must point to dynamic memory)..
  auto val = 123;
  cout << "create another pointer pInt with " << val << endl;
  std::weak_ptr< int > pInt( new int(val) );

  // release the pointer to a raw pointer
// TODO dangling
// TODO conversion to shared_ptr?

//  auto *pVal = pInt.release();
//  cout << "yet another smartpointer, the raw pointer '*pVal' shows: " << *pVal << endl;
// */


  cout << "READY." << endl;

  return EXIT_SUCCESS;
}
