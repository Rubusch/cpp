/*
  C++11 - use 'std::weak_ptr' for 'std::shared_ptr' like pointers that can dangle
  (Meyers / item 20)

  NOTE
  - 'std::weak_ptr' can dangle!
  - 'std::weak_ptr' can't be dereferenced (conversion to a 'std::shared_ptr' via lock(), then dereference the 'std::shared_ptr')
  - 'std::weak_ptr' can't be tested for nullness
  - 'std::weak_ptr' is an augmentation to 'std::shared_ptr' and not a standalone smartpointer

  CONCLUSION
  

  resource: Effective Modern C++, Scott Meyers, 2015

  'std::shared_ptr' is a typical implementation of 'std::weak_ptr'
  - a pointer to the control block; and
  - the stored pointer of the shared_ptr it was constructed from

  resource: cppreference.com

 @author: lothar Rubusch
 */

#include <iostream>
#include <memory> /* weak_ptr */
#include <exception> /* exception */

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
  cout << endl;

  cout << "assign pBox to pAnotherBox" << endl;
  pAnotherBox = pBox;

  // get content of weak pointer: lock() converts to shared_ptr
  // a 'std::weak_ptr' can dangle i.e. the returned pointer needs not to be valid!
  if (auto content = pAnotherBox.lock()) cout << "pAnotherBox contains " << content->box_content() << " toys" << endl;
  else cout << "FAILED! pAnotherBox has no content" << endl;
  cout << endl;

  // check if a pointer is empty
  cout << "now reset shared_ptr pBox" << endl;
  pBox.reset();
  if (!pBox) cout << "pBox has no content" << endl;
  else  cout << "FAILED" << endl;

  // get content of weak pointer: lock() converts to shared_ptr
  // a 'std::weak_ptr' can dangle i.e. the returned pointer needs not to be valid!
  if (auto content = pAnotherBox.lock()) cout << "FAILED! pAnotherBox contains " << content->box_content() << " toys" << endl;
  else cout << "pAnotherBox has no content" << endl;
  cout << endl;


  // 'std::weak_ptr's that dangle are said to have 'expired'
  if (pAnotherBox.expired()) cout << "pAnotherBox has expired i.e. is a dangling pointer" << endl;
  cout << endl;


  // 'std::weak_ptr's can be converted to 'std::shard_ptr's via constructor
  // if the 'std::weak_ptr' is a dangling pointer, an exception is thrown
  cout << "conversion to shared_ptr is possible, but may fail if weak_ptr is dangling" << endl;
  try {
    std::shared_ptr< Box > pConversionBox( pAnotherBox );
  } catch (bad_weak_ptr &e) {
    cout << "exception: " << e.what() << endl;
  }
  cout << endl;


  cout << "READY." << endl;

  return EXIT_SUCCESS;
}
