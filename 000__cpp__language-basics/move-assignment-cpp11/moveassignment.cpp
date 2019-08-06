/*
  move assinment

 in context of move and copy constructors:
 - a copy constructor creates a deep copy of an object with out changing the object's content
 - a move constructor creates a deep copy of an object, allowing to change even the object itself (rhs)

 purpose:
 - performance increase and under the hood optimizations when using STL containers (return value optimization, rvo)
 - non-copiable objects: parallel execution of a function of a non-copiable object e.g. inside threads

 caution:
 use of moved objects after the move can implicitely be dangerous,
 but is guaranteed for the STL and should always be implemented as best practice
 */

#include <iostream>
#include <string>

using namespace std;


class Box
{
private:
  string *pItem = nullptr;
  string anotherItem;

public:
  Box()
  {
    cout << "OP: constructor" << endl;
  }

  Box(string* item)
  : pItem(item)
  {
    cout << "OP: constructor" << endl;
    anotherItem = string("mouse");
  }

  // copy constructor (deep copy)
  Box(const Box& cpy)
  {
    cout << "OP: copy constructor" << endl;
    if (this == &cpy) return;

    if (nullptr != pItem) delete pItem;
    pItem = new string(*cpy.pItem);
    anotherItem = cpy.anotherItem;
  }

  // move constructor (deep reference)
  Box(Box&& mve) noexcept
  {
    cout << "OP: move constructor" << endl;
    if (this == &mve) return;

    pItem = mve.pItem;
    mve.pItem = nullptr;

    anotherItem = mve.anotherItem;
  }

  ~Box()
  {
    cout << "OP: destructor" << endl;
    if (pItem) delete pItem;
  }

  // assignment operator
  Box& operator=(Box& rhs)
  {
    cout << "OP: assignment operator" << endl;
    if (this != &rhs) {
      if (nullptr != pItem) delete pItem;
      pItem = new string(rhs.getItem());
      anotherItem = rhs.getAnotherItem();
    }
    return *this;
  }

  // assignment move operator
  Box& operator=(Box&& rhs)
  {
    cout << "OP: assignment move operator" << endl;
    if (this != &rhs) {
      if (nullptr != pItem) delete pItem;
      pItem = &rhs.getItem();
      anotherItem = rhs.getAnotherItem();
      rhs.setItem(nullptr);
    }
    return *this;
  }

  constexpr string& getItem() { return *pItem; }
  void setItem(string* pItem) { pItem = pItem; }
  constexpr string& getAnotherItem() { return anotherItem; }
  string isItem() { return ((nullptr == pItem) ? "NULL, getItem() would end in 'Segmentation Fault!'" : "allocated" ); }
};



int main(void)
{
  string *pAnimal = new string("elephant");
  cout << "addr of pAnimal: \t\t" << pAnimal << endl << endl;

  Box box(pAnimal);

  // the box itself

  cout << "addr of 'box': \t\t\t\t" << &box << endl;
  cout << "addr of 'box::pItem': \t\t\t" << &box.getItem() << " <- same as pAnimal, since there allocated" << endl;
  cout << "addr of 'box::anotherItem': \t\t" << &box.getAnotherItem() << endl;
  cout << endl;

  // a reference (all addresses are identical)
  Box &referenceBox = box;

  cout << "addr of 'ref-box' reference: \t\t" << &referenceBox << endl;
  cout << "addr of 'ref-box::pItem': \t\t" << &referenceBox.getItem() << endl;
  cout << "addr of 'ref-box::anotherItem': \t" << &referenceBox.getAnotherItem() << endl;
  cout << endl;

  // a pointer
  Box *pointerBox = &box;

  cout << "addr of 'ptr-box' pointer: \t\t" << &pointerBox << " <-- pointer has a different address" << endl;
  cout << "addr of 'ptr-box::pItem': \t\t" << &pointerBox->getItem() << endl;
  cout << "addr of 'ptr-box::anotherItem': \t" << &pointerBox->getAnotherItem() << endl;
  cout << endl;

  // via copy constructor
  Box copyBox(box);

  cout << "addr of 'cp-box' pointer: \t\t" << &copyBox << " <-- deep copy differs" << endl;
  cout << "addr of 'cp-box::pItem': \t\t" << &copyBox.getItem() << " <-- deep copy differs" << endl;
  cout << "addr of 'cp-box::anotherItem': \t\t" << &copyBox.getAnotherItem() << " <-- deep copy differs" << endl;
  cout << endl;

  // via copy assignment
  Box backupBox;
  backupBox = box;

  cout << "addr of 'asn-box' pointer: \t\t" << &backupBox << " <-- deep copy differs" << endl;
  cout << "addr of 'asn-box::pItem': \t\t" << &backupBox.getItem() << " <-- deep copy differs" << endl;
  cout << "addr of 'asn-box::anotherItem': \t" << &backupBox.getAnotherItem() << " <-- deep copy differs" << endl;
  cout << endl;

  // via move constructor - call of 'move' will use the move constructor
  Box movedBox = std::move(box);

  cout << "addr of 'move-ctr-box' pointer: \t" << &movedBox << " <-- deep copy differs" << endl;
  cout << "addr of 'move-ctr-box::pItem': \t\t" << &movedBox.getItem() << " <-- SAME as box::pItem!!!" << endl;
  cout << "addr of 'move-ctr-box::anotherItem': \t" << &movedBox.getAnotherItem() << endl;
  cout << endl;

  cout << "addr of the original box::pItem == null? \t" << box.isItem() << endl << endl;

  // via move operator - separate instantiation and assignment
  Box movingBox;
  movingBox = std::move(movedBox);

  cout << "addr of 'move-box' pointer: \t\t" << &movingBox << " <-- deep copy differs" << endl;
  cout << "addr of 'move-box::pItem': \t\t" << &movingBox.getItem() << " <-- SAME as box::pItem!!!" << endl;
  cout << "addr of 'move-box::anotherItem': \t" << &movingBox.getAnotherItem() << endl;
  cout << endl;

  cout << "addr of the original movedBox::pItem == null? \t" << box.isItem() << endl << endl;

  cout << "READY." << endl;

  exit(EXIT_SUCCESS);
}
