/*
  C++11 - prefer override functions (Meyers / item 12)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - declare overriding functions override

  - member function reference qualifiers make it possible to treat lvalue and
    rvalue objects e.g. *this differently

  - 'virtual' functions can be ovewritten, 'override' declared functions must be
    overwritten

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <memory>

using namespace std;


class Base
{
public:
  virtual void doWork()
  {
    cout << "CALLED: Base::doWork();" << endl;
  }
};


class Derived : public Base
{
public:
  virtual void doWork() // virtual is optional here, all derived class'es virtual functions are virtual, too
  {
    cout << "CALLED: Derived::doWork();" << endl;
  }
};


int main(void)
{
  cout << "init 'unique_ptr<Base> upb = make_unique<Derived>();'" << endl;
  std::unique_ptr<Base> upb = std::make_unique<Derived>();

  upb->doWork();
  // TODO

  cout << "READY." << endl;
}

