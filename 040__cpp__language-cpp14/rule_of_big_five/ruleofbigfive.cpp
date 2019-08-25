/*
 rule of big five

 1/5 copy assingment constructor
 2/5 copy move constructor
 3/5 assignment operator
 4/5 assignment move operator
 5/5 destructor


 in context of move and copy constructors:
 - a copy constructor creates a deep copy of an object with out changing the object's content
 - a move constructor creates a deep copy of an object, allowing to change even the object itself (rhs)

 purpose of move:
 - performance increase and under the hood optimizations when using STL containers (return value optimization, rvo)
 - non-copiable objects: parallel execution of a function of a non-copiable object e.g. inside threads

 caution:
 use of moved objects after the move can implicitely be dangerous,
 but is guaranteed for the STL and should always be implemented as best practice

 if move is applied to e.g. 'const string' or any other const, move will rather copy the content than move anything!
 (Item 23, Effective Modern C++, Meyers, 2015)

 @author: lothar Rubusch
 */

#include <iostream>
#include <string>

using namespace std;


class Box
{
private:
  const string *pItem = nullptr;


public:
  Box()
  {
    cout << "CALLED: constructor" << endl;
  }

  Box(string* item)
  : pItem(item)
  {
    cout << "CALLED: constructor with argument" << endl;
  }

  // copy assignment constructor (deep copy)
  Box(const Box& cpy)
  {
    cout << "CALLED: copy assignment constructor (1/5)" << endl;
    if (this == &cpy) return;

    pItem = new string(*cpy.pItem); // deep copy
  }

  // copy move constructor (deep reference - may destroy moved original)
  Box(Box&& mve) noexcept
  {
    cout << "CALLED: copy move constructor (3/5)" << endl;
    if (this == &mve) return;

    pItem = mve.pItem;
    mve.pItem = nullptr;

  }

  // destructor
  ~Box()
  {
    cout << "CALLED: destructor (5/5)" << endl;
    if (pItem) delete pItem;
    pItem = nullptr;
  }

  // assignment operator
  Box& operator=(Box& rhs) noexcept
  {
    cout << "CALLED: assignment operator (2/5)" << endl;
    if (this != &rhs) {
      if (pItem) delete pItem; // avoid memory leak
      pItem = new string(rhs.getItem()); // deep copy
    }
    return *this;
  }

  // assignment move operator
  Box& operator=(Box&& rhs) noexcept
  {
    cout << "CALLED: assignment move operator (4/5)" << endl;
    if (this != &rhs) {
      if (pItem) delete pItem; // avoid memory leak
      pItem = &rhs.getItem();
      rhs.setItem(nullptr);
    }
    return *this;
  }

  const string& getItem()
  {
    return *pItem;
  }

  void setItem(const string* item)
  {
    pItem = item;
  }
};



int main(void)
{
  string *pStr = new string("elephant");
  cout << "addr of pStr: \t\t\t\t" << pStr << endl << endl;

  // the box itself
  Box box(pStr);
  cout << "addr of 'box::pItem': \t\t\t" << &box.getItem() << " <- same as pStr, since there allocated" << endl;
  cout << endl;

  // call copy assignment constructor
  Box copyBox(box);
  cout << "addr of 'cp-box::pItem': \t\t" << &copyBox.getItem() << " <-- deep copy, differs" << endl;
  cout << endl;

  // call copy assignment operator
  Box backupBox;
  backupBox = box;
  cout << "addr of 'asn-box::pItem': \t\t" << &backupBox.getItem() << " <-- deep copy differs" << endl;
  cout << endl;

  // call copy move constructor
  Box movedBox = std::move(box);
  cout << "addr of 'move-ctr-box::pItem': \t\t" << &movedBox.getItem() << " <-- SAME as box::pItem!!!" << endl;
  cout << "addr of 'box::pItem': \t\t\t" << &box.getItem() << " <-- now is null" << endl;
  cout << endl;

  // call copy move operator - separate instantiation and assignment needed
  Box movingBox;
  movingBox = std::move(movedBox);
  cout << "addr of 'moving-box::pItem': \t\t" << &movingBox.getItem() << " <-- SAME as move-ctr-box::pItem!!!" << endl;
  cout << "addr of 'movedbox::pItem': \t\t" << &movedBox.getItem() << " <-- now is null" << endl;
  cout << endl;

  cout << "READY." << endl;

//  exit(EXIT_SUCCESS);
}
