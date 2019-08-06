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
  Box(string* item)
  : pItem(item)
  {
    anotherItem = string("mouse");
  }

  // copy constructor
  Box(const Box& cpy)
  {
    if (this == &cpy) return;

    pItem = new string(*cpy.pItem);
    anotherItem = cpy.anotherItem;
  }

  // move constructor
  Box(Box&& mve) noexcept
  {
    if (this == &mve) return;

    pItem = new string(*mve.pItem);
    delete mve.pItem; mve.pItem = nullptr;

    anotherItem = mve.anotherItem;
  }

  ~Box()
  {
    if (pItem) delete pItem;
  }

  constexpr string& getItem() { return *pItem; }
  constexpr string& getAnotherItem() { return anotherItem; }
  const string isItem() { return ((nullptr == pItem) ? "NULL, getItem() would end in 'Segmentation Fault!'" : "allocated" ); }
};



int main(void)
{
  string *pAnimal = new string("elephant");
  cout << "addr of pAnimal: \t\t" << pAnimal << endl << endl;

  Box box(pAnimal);

  // the box itself

  cout << "addr of 'box': \t\t\t" << &box << endl;
  cout << "addr of 'box::item': \t\t" << &box.getItem() << " <- same as pAnimal, since there allocated" << endl;
  cout << "addr of 'box::anotherItem': \t" << &box.getAnotherItem() << endl;
  cout << endl;

  // a reference (all addresses are identical)
  Box &referenceBox = box;

  cout << "addr of 'box' reference: \t" << &referenceBox << endl;
  cout << "addr of 'box::item': \t\t" << &referenceBox.getItem() << endl;
  cout << "addr of 'box::anotherItem': \t" << &referenceBox.getAnotherItem() << endl;
  cout << endl;

  // a pointer
  Box *pointerBox = &box;

  cout << "addr of 'box' pointer: \t\t" << &pointerBox << " <-- pointer has a different address" << endl;
  cout << "addr of 'box::item': \t\t" << &pointerBox->getItem() << endl;
  cout << "addr of 'box::anotherItem': \t" << &pointerBox->getAnotherItem() << endl;
  cout << endl;

  // via copy constructor
  Box copyBox(box);

  cout << "addr of 'box' pointer: \t\t" << &copyBox << " (deep copy differs)" << endl;
  cout << "addr of 'box::item': \t\t" << &copyBox.getItem() << " (differs)" << endl;
  cout << "addr of 'box::anotherItem': \t" << &copyBox.getAnotherItem() << " (differs)" << endl;
  cout << endl;

  // via move
  Box moveBox = std::move(box);

  cout << "addr of 'box' pointer: \t\t" << &moveBox << " (deep copy differs)" << endl;
  cout << "addr of 'box::item': \t\t" << &moveBox.getItem() << " (differs)" << endl;
  cout << "addr of 'box::anotherItem': \t" << &moveBox.getAnotherItem() << " (differs)" << endl;
  cout << endl;

  cout << "addr of box::item == null? \t" << box.isItem() << endl;

  cout << "READY." << endl;

  exit(EXIT_SUCCESS);
}
