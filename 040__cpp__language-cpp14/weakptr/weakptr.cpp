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
  cout << endl;

  cout << "assign pBox to pAnotherBox" << endl;
  pAnotherBox = pBox;

  // get content of weak pointer: lock() converts to shared_ptr
  if (auto content = pAnotherBox.lock()) cout << "pAnotherBox contains " << content->box_content() << " toys" << endl;
  else cout << "FAILED! pAnotherBox has no content" << endl;
  cout << endl;

  // check if a pointer is empty
  cout << "now reset shared_ptr pBox" << endl;
  pBox.reset();
  if (!pBox) cout << "pBox has no content" << endl;
  else  cout << "FAILED" << endl;

  // get content of weak pointer: lock() converts to shared_ptr
  if (auto content = pAnotherBox.lock()) cout << "FAILED! pAnotherBox contains " << content->box_content() << " toys" << endl;
  else cout << "pAnotherBox has no content" << endl;
  cout << endl;


  cout << "READY." << endl;

  return EXIT_SUCCESS;
}
