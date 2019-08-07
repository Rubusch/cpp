// lambda.cpp
/*
  demonstrates lambdas (>=cpp11)
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

// TODO
  cout << "READY." << endl;
}

