/*
  C++11 - prefer unique_ptr to auto_ptr and raw pointers
  (Meyers / item 18)

  unique_ptr is always the unique owner of the raw pointer resource!
  thus a unique_ptr object cannot be copied - only moved (i.e. the
  moving pointer looses its ownership, can mean it will be destroyed
  after moving)

  demonstrates basic operations with unique_ptr
  resources: Effective Modern C++, Scott Meyers, 2015

 @author: Lothar Rubusch <L.Rubusch@gmail.com>
 */

#include <iostream>
#include <memory> /* unique_ptr */

using namespace std;


class Box
{
private:
  int number_of_toys;

public:
  auto box_content() const { return number_of_toys; }
  void open() { cout << "..xaSATXsx.." << endl; }

  ~Box() { cout << "CALLED: ~Box()" << endl; }
  Box(int number) : number_of_toys(number)
  {
    cout << "CALLED: Box(" << number << ")" << endl;
  }
};


void unpack(std::unique_ptr< Box > &box)
{
  cout << "let's open the box: ";
  box->open();
}


int main(void)
{
  // creating a pointer and initialization
  /*
    std::unique_ptr< Box > pBox( new Box(12) );
  /*/
  // prefer make_unique() and make_shared() to new semantics
  auto pBox = make_unique< Box >(12);
  // */

  // creation of an empty pointer is possible
  std::unique_ptr< Box > pAnotherBox;

  // check if a pointer is empty
  if (!pAnotherBox) {
    cout << "there is no pAnotherBox content" << endl;
  }

  // check if a pointer is empty
  auto content = pBox->box_content();
  cout << "the pBox contains " << content << " toys" << endl;

  // pass the unique_ptr by reference
  unpack(pBox);

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
