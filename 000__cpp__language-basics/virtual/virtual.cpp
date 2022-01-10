// Main.cpp
/*
  Inheritance and abstract base class

  Only one pure virtual function is enough to make a class abstract.
  Use Virtual Functions for functions to be overwritten (dynamic
  binding).

  Without "virtual" you have static binding with some side effects at
  overwriting a method.

  Virtual base classes should not have member variables.



  Controlled Polymorphism - Liskov Substitution Principle (LSP)

  * IS-A relation: public inheritance

  * IS-A / WORKS-AS / CAN-BE-USED-AS: private and protected inheritance,
    respectively

  * HAS-A relation: member variable or pointer (aggregation)

  * IS-IMPLEMENTED-WITH: implementation pointer as a member



  Generally prefer looser relations!!!

  Closer:                                                    Looser:

  friend / compositn. < pub. inhrit. < priv. inhrit. < aggr. < assoc.


  ---

  Member functions can be
  * hidden: without any 'virtual' declaration functions in Base are
    not reachable at assignments, such as (might need down cast at
    dynamic binding):

        Base* pB = new Derived();

    Hidden functions in Base can be accessed via using the Base
    namespace, too.

  * virtual: virtual functions in Base can be overwritten. One or more
    pure virtual functions make the class 'abstract'. Base classes
    always need a virtual destructor!

  * override: functions that must be re-implemented in a derived class

  * final: virtual functions that cannot be overwritten anymore

  * try to avoid public virtual method, in favor of the Template
    Pattern


  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  Generally try to avoid inheritance in favor of aggregation patterns.
  Inheritance is only needed when virtual functions (functions need to
  be overwriteable), or members are within a protected block are
  around. By Liskov public inheritance implements a 'IS-A'
  relation. Everything else should be modeled as aggregation 'HAS-A',
  or 'IS-IMPLEMENTED-WITH' (which can also be private
  inheritance). [Sutter, 2000]

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



  RESOURCES

  Exceptional C++, Herb Sutter, 2000
*/

#include <iostream>
#include <string>

using namespace std;


class Bird;
class Pinguin;
class Vulture;
class Eagle;


class Bird
{
public:
  void name() { cout << "Bird"; };
  virtual void sound() { cout << "nothing"; };
  // pure virtual function - makes the class abstract
  virtual void fly() {}; // = 0; /* ideally make this class abstract */
};


class Pinguin : public Bird
{
public:
  void name() { cout << "Pinguin"; };
  void sound() // virtual in base
  {
    cout << "blob";
  };
  void fly() // pure virtual in base
  {
    cout << "swims";
  };
};


class Vulture : public Bird
{
public:
  void name() { cout << "Vulture"; };
  void sound() // virtual in base
  {
    Bird::sound();
  };
  void fly() // pure virtual in base
  {
    cout << "flies";
  };
};


class Eagle : public Bird
{
public:
  void name() { cout << "Eagle"; };
  void sound() // virtual in base
  {
    cout << "aaaaa";
  };
  void fly() // pure virtual in base
  {
    cout << "flies";
  };
};


int main()
{
  Pinguin *p = new Pinguin();
  cout << "The ";
  p->name();
  cout << ' ';
  p->fly();
  cout << " and says: ";
  p->sound();
  cout << '.' << endl;

  // use derived class instance
//  Vulture *v = new Vulture();

  // use base class pointer (w/o dynamic_cast stays baseclass)
  Bird *v = new Vulture();
  cout << "The ";
  v->name();
  cout << ' ';
  v->fly();
  cout << " and says: ";
  v->sound();
  cout << '.' << endl;

  Eagle *e = new Eagle();
  cout << "The ";
  e->name();
  cout << ' ';
  e->fly();
  cout << " and says: ";
  e->sound();
  cout << '.' << endl;

  delete p;
  delete v;
  delete e;

  return 0;
};
