// copy_constructor.cpp
/*
  demonstrates a copy constructor - cpy ctor

  Use the copy constructor especially for classes with dynamically allocated memory!

  (11/Meyers)
//*/

#include <iostream>

using namespace std;


class Box
{
private:
  const string *pItem = nullptr;

public:
  Box(const string *item)
  {
    cout << "CALLED: constructor" << endl;

    pItem = item;
  }

  // copy constructor
  //
  // The copy constructor is a special function:
  // Doesn't matter if these were declared "private" or "protected" - the access within
  // the copy constructor works like a friend declared function!! Everything's "public"
  // here!
  Box(const Box& box)
  {
    cout << "CALLED: copy assignment constructor" << endl;

    if (this == &box) return;

    // deep copy!
    //
    // this has to be another allocation!
    // if it was just a reference to the orig element, calling 'delete' in on of both
    // objects on 'pItem' will result in unallocated memory in the other object for
    // 'pItem'
    pItem = new string(*box.pItem);
  }

  // destructor
  // - if the class would have a virtual function, the destructor should be virtual, too
  // - a class that has member pointers, should have an self implemented destructor
  // - delete should happen where the allocation has happened -> no allocation, no delete!
  ~Box()
  {
    cout << "CALLED: destructor" << endl;

    if (nullptr != pItem) delete pItem;
    pItem = nullptr;
  }

  // some getter
  const string* getItem() const
  {
    return pItem;
  }
};


int main(void)
{
  string *pStr = new string("Perikles");
  cout << "Address of pStr target (pointee): \t" << pStr << endl;
  cout << endl;

  Box box(pStr);
  cout << "Address of box: \t\t\t" << &box << endl;
  cout << "Address of box.pItem: \t\t\t" << box.getItem() << " <-- identical with pointee" << endl;
  cout << endl;

  Box bigbox(box);
  cout << "Address of bigbox: \t\t\t" << &bigbox << endl;
  cout << "Address of bigbox.pItem: \t\t" << bigbox.getItem() << " <-- different" << endl;
  cout << endl;

  cout << "READY." << endl;
}

