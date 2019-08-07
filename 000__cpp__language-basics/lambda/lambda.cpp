// lambda.cpp
/*
  demonstrates lambdas (>=cpp11)

  syntax variants:
  [capture] (params) mutable exception attribute -> ret { body }
  [capture] (params) -> ret { body }
  [capture] (params) { body }
  [capture] { body }

  where:
  mutable = allows the body to modify copied params and to call their non-const member functions
  exception = exception specification, or noexcept
  attribute = attribute specificatio for the closure type

  capture = which symbols are captured and thus visible for the lambda body
  e.g.
    [a,&b]   a as by value copy, b as reference
    [this]   this pointer as a by value copy
    [&]      all symbols available in function scope as reference
    [=]      all symbols available in function scoe as a copy
    []       nothing captured

  params = list of parameters
  ret = return type, defaults to "void"

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

