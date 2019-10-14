// operator move - no, actually the assignment move operator
/*
  move is called via std::move() or inside the stl for certain operations,
  e.g. swap, it improves performance, and when using the STL might be applied
  implicitely also in older codes by recompilation

  the following demonstrates writing a move operator and how the content of
  objects should behave
//*/

#include <iostream>

using namespace std;


class Box
{
private:
  const string *pItem = nullptr;

public:
  Box() { cout << "CALLED: constructor" << endl; }

  Box(const string *item)
  {
    cout << "CALLED: constructor with argument" << endl;

    pItem = item;
  }

  // copy move constructor
  //
  // The copy constructor is a special function:
  // Doesn't matter if these were declared "private" or "protected" - the access
  // within the copy constructor works like a friend declared function!!
  // Everything's "public" here!
  Box &operator=(Box &&box)
  {
    cout << "CALLED: assignment move operator" << endl;

    if (this != &box) {
      // avoid memory leaks
      if (pItem)
        delete pItem;

      // deep move (reference)!
      //
      // the move passes the content to the receiving object, the moved one may
      // lose its contents or allocations entirely (needs care of explicit
      // implementation)
      pItem = box.pItem;
      box.pItem = nullptr;
    }
    return *this;
  }


  // destructor
  // - if the class would have a virtual function, the destructor should be
  // virtual, too
  // - a class that has member pointers, should have an self implemented
  // destructor
  // - delete should happen where the allocation has happened -> no allocation,
  // no delete!
  ~Box()
  {
    cout << "CALLED: destructor" << endl;

    if (nullptr != pItem)
      delete pItem;
    pItem = nullptr;
  }

  // some getter
  const string *getItem() const { return pItem; }
};


int main(void)
{
  string *pStr = new string("Perikles");
  cout << "Address of pStr target (pointee): \t" << pStr << endl;
  cout << endl;

  Box box(pStr);
  cout << "Address of box: \t\t\t" << &box << endl;
  cout << "Address of box.pItem: \t\t\t" << box.getItem()
       << " <-- identical with pointee" << endl;
  cout << endl;

  // to call the assignment move operator, both objects already need to be
  // instantiated
  Box bigbox;
  bigbox = std::move(box);
  cout << "Address of bigbox: \t\t\t" << &bigbox << endl;
  cout << "Address of bigbox.pItem: \t\t" << bigbox.getItem()
       << " <-- also identical (moved content)" << endl;
  cout << endl;

  cout << "Address of box.pItem: \t\t\t" << box.getItem()
       << " <-- original reset to 'nullptr'" << endl;
  cout << endl;

  cout << "READY." << endl;
}
