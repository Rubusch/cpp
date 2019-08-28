/*
  C++11 - prefer final functions (Meyers / item 12)

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


// C++11 feature 'final' and 'override'
class BaseNew
{
public:
  virtual void mf1() const
  {
    cout << "CALLED: BaseNew::mf1() const" << endl;
  }

  virtual void mf2(int x)
  {
    cout << "CALLED: BaseNew::mf2(int)" << endl;
  }

  virtual void mf3() & final
  {
    cout << "CALLED: BaseNew::mf3() & final" << endl;
  }

  virtual void mf4() const final
  {
    cout << "CALLED: BaseNew::mf4() final" << endl;
  }
};

class DerivedNew : public BaseNew
{
public:
  virtual void mf1() const override // 'override' is declared in the derived function
  {
    cout << "CALLED: DerivedNew::mf1() const" << endl;
  }

  virtual void mf2(int x) override
  {
    cout << "CALLED: DerivedNew::mf2(int)" << endl;
  }
};


int main(void)
{
  cout << "override solves several situations" << endl;
  unique_ptr<BaseNew> upbn = make_unique<DerivedNew>();
  upbn->mf1();
  upbn->mf2(78);
  upbn->mf3();
  upbn->mf4();
  cout << endl;

  cout << "READY." << endl;
}

