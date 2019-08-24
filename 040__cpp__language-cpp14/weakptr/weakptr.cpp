/*
  C++11 - use 'std::weak_ptr' for 'std::shared_ptr' like pointers that can dangle
  (Meyers / item 20)


  resources: Effective Modern C++, Scott Meyers, 2015

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
  std::weak_ptr< Box > pBox( new Box(12) );

  // creation of an empty pointer is possible
  std::weak_ptr< Box > pAnotherBox;

  // check if a pointer is empty
  if (!pAnotherBox) {
    cout << "there is no pAnotherBox content" << endl;
  }

  // check if a pointer is empty
  auto content = pBox->box_content();
  cout << "the pBox contains " << content << " toys" << endl;

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



  cout << "READY." << endl;

  return EXIT_SUCCESS;
}
