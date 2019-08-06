// copy_constructor.cpp
/*
  demonstrates writing a move operator
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

  // copy move constructor
  //
  // The copy constructor is a special function:
  // Doesn't matter if these were declared "private" or "protected" - the access within
  // the copy constructor works like a friend declared function!! Everything's "public"
  // here!
  Box(Box&& box) noexcept
  {
    cout << "CALLED: copy move constructor" << endl;

    if (this == &box) return; // actually interesting in case of move...

    // deep move (reference)!
    //
    // the move passes the content to the receiving object, the moved one may lose its
    // contents or allocations entirely (needs care of explicit implementation)
    pItem = box.pItem;
    box.pItem = nullptr;
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

  Box bigbox = std::move(box);
  cout << "Address of bigbox: \t\t\t" << &bigbox << endl;
  cout << "Address of bigbox.pItem: \t\t" << bigbox.getItem() << " <-- also identical (moved content)" << endl;
  cout << endl;

  cout << "Address of box.pItem: \t\t\t" << box.getItem() << " <-- original reset to 'nullptr'" << endl;
  cout << endl;

  cout << "READY." << endl;
}

