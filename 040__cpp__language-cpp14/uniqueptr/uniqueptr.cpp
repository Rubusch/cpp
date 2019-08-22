/*
  C++11 - prefer unique_ptr to auto_ptr and raw pointers (Meyers / item 18)

  unique_ptr is always the unique owner of the raw pointer resource!
  thus a unique_ptr object cannot be copied - only moved (i.e. the moving
  pointer looses its ownership, can mean it will be destroyed after moving)

  demonstrates basic operations with unique_ptr

 @author: lothar Rubusch
 */

#include <iostream>
#include <memory> /* unique_ptr */

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
  std::unique_ptr< Box > pBox( new Box(12) );

  // creation of an empty pointer is possible
  std::unique_ptr< Box > pAnotherBox;

  // check if a pointer is empty
  if (!pAnotherBox) {
    cout << "there is no other box" << endl;
  }

  // check if a pointer is empty
  auto content = pBox->box_content();
  cout << "the box contains " << content << " toys" << endl;

  // ERROR: not copyable
//  std::unique_ptr< Box > pCopyBox = pBox;

  // BUT: moveable
  pAnotherBox = std::move(pBox);

  // the moving pointer is now obsolete
  if (nullptr == pBox) {
    cout << "the box disappeared...." << endl;
  }
  cout << "the moved box contains " << pAnotherBox->box_content() << " toys" << endl;

  // reset a unique_ptr
  cout << "trash the box" << endl;
  pAnotherBox.reset();


  // creating (must point to dynamic memory)..
  auto val = 123;
  cout << "create another pointer with " << val << endl;
  std::unique_ptr< int > pInt( new int(val) );

  // release the pointer to a raw pointer
  auto *pVal = pInt.release();
  cout << "yet another smartpointer, the raw pointer '*pVal' shows: " << *pVal << endl;


  cout << "READY." << endl;

  return EXIT_SUCCESS;
}
