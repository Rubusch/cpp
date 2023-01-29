/*
  C++11 - prefer unique_ptr

  unique_ptr is always the unique owner of the raw pointer resource!
  thus a unique_ptr object cannot be copied - only moved (i.e. the
  moving pointer looses its ownership, can mean it will be destroyed
  after moving)

  demonstrates a getter to unique_ptr items

 @author: Lothar Rubusch <L.Rubusch@gmail.com>
 */

#include <iostream>
#include <memory> /* unique_ptr */
#include <string> /* string_view since C++ 17 */

using namespace std;

struct Banana
{
  int number;

  void say()
  {
    cout << "banana says: " << "HELLO BANANA! (" << number << ")" << endl;
  }

  Banana()
    : number(0)
  {}
};


class Box
{
public:
  unique_ptr< Banana > pBanana;

  // to compare a regular pointer
  Banana arr[2];
  Banana *pArrOne = nullptr;

  Box()
  {
    // init smart pointer
    pBanana = unique_ptr< Banana >(new Banana());

    // init regular pointer
    pArrOne = &arr[1];

    cout << "CALLED: Box()" << endl;
  }
  ~Box()
  {
    cout << "CALLED: ~Box()" << endl;
  }

  Banana* getPtr() const
  {
    return pBanana.get();
  }

  Banana& getRef() const
  {
    return *pBanana;
  }

  unique_ptr< Banana > getMovedPtr()
  {
    return move(pBanana);
  }


  // regular (old) access
  Banana* getRegularPtr() const
  {
    return pArrOne;
  }

  Banana& getRegularRef() const
  {
    return *pArrOne;
  }
};


int main(void)
{
  // creating a pointer and initialization
  std::unique_ptr< Box > box( new Box() );


  cout << "pointer, inlined:" << endl;
  {
    box->getPtr()->say();
  }
  cout << endl;


  cout << "pointer, via pointer:" << endl;
  {
    Banana *ptr = box->getPtr();
    ptr->say();
  }
  cout << endl;


  cout << "reference:" << endl;
  {
    Banana ref = box->getRef();
    ref.say();
  }
  cout << endl;


  cout << "moved:" << endl;
  {
    unique_ptr< Banana > movedptr = box->getMovedPtr();
    movedptr->say();
  }
  cout << endl;


  cout << "regular pointer with *:" << endl;
  {
    Banana *ptr = box->getRegularPtr();
    ptr->say();
    cout << "...put something into" << endl;
    ptr->number++;
  }
  cout << endl;


  cout << "regular reference with &:" << endl;
  {
    Banana& ref = box->getRegularRef();
    ref.say();
    cout << "...put something into" << endl;
    ref.number++;
  }
  cout << endl;


  cout << "check object member:" << endl;
  {
    cout << "FINAL NUMBER: " << box->arr[1].number << endl;
  }
  cout << endl;

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
