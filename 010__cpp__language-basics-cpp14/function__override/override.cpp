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


// C++98 'virtual' functions
//
// * the base class function mus be virtual
// * the base and derived function names must be identical (except in the case of destructors)
// * the parameter types of the base and derived functions must be identical
// * the constness of the base and derived functions must be identical
// * the return types and exception specifications of the base and derived functions must be compatible
// * all derived virtual functions are automatically virtual
// * virtual functions can be overwritten, but need not to be
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


// rvalue and lvalue example
class Widget
{
public:
  void doWork() & // applies only when *this is an lvalue
  {
    cout << "CALLED: Widget::doWork() [lvalue]" << endl;
  }

  void doWork() && // applies only when *this is an rvalue
  {
    cout << "CALLED: Widget::doWork() [rvalue]" << endl;
  }

};

Widget makeWidget()
{
  return Widget();
}


// C++11 feature 'override'
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

  virtual void mf3() &
  {
    cout << "CALLED: BaseNew::mf3() &" << endl;
  }

  virtual void mf4() const
  {
    cout << "CALLED: BaseNew::mf4()" << endl;
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

  virtual void mf3() & override
  {
    cout << "CALLED: DerivedNew::mf3() &" << endl;
  }

  void mf4() const override // adding virtual here is ok, but not needed
  {
    cout << "CALLED: DerivedNew::mf4()" << endl;
  }
};


int main(void)
{
  cout << "classic: init 'unique_ptr<Base> upb = make_unique<Derived>();'" << endl;
  std::unique_ptr<Base> upb = std::make_unique<Derived>();
  upb->doWork();
  cout << endl;

  cout << "classic: lvalue and rvalue calls on member functions" << endl;
  Widget wg;
  cout << "wg.doWork()" << endl;
  wg.doWork();
  cout << endl;

  cout << "makeWidget().doWork()" << endl;
  makeWidget().doWork();
  cout << endl;

  cout << "override solves several situations" << endl;
  unique_ptr<BaseNew> upbn = make_unique<DerivedNew>();
  upbn->mf1();
  upbn->mf2(78);
  upbn->mf3();
  upbn->mf4();
  cout << endl;

  cout << "READY." << endl;
}

