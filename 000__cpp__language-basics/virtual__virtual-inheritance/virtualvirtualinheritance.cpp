// nonvirtualinheritance.cpp
/*
  virtual inheritance - in a "diamond" situation, EACH derived class
  will have the SAME base instance. Modified attributes in a base class
  will be commonly shared!

             +-----------+
             | Base (1)  |
             +-----------+
                  /_\
                   |
        +----------+----------+
        |                     |
  +-----------+         +-----------+
  | DerivedA  |         | DerivedB  |
  +-----------+         +-----------+
       /_\                   /_\
        |                     |
        +----------+----------+
                   |
             +-----------+
             | Client    |
             +-----------+
//*/


#include <iostream>


/*
  Base
//*/
class Base
{
protected:
  int variable;

public:
  virtual ~Base(){}
  void display()
  {
    std::cout << "Base::variable = " << variable << "\n";
  }
};


/*
  DerivedA

  if this inheritance doesn't have "virtual" the class would have a separate
  "base" instance - "variable" would be different!
//*/
class DerivedA
  : public virtual Base
{
public:
  DerivedA()
  {
    variable = 1;
  }

  virtual ~DerivedA(){}

  void display_derivedA()
  {
    std::cout << "DerivedA -> Base::variable = " << variable << "\n";
  }
};


/*
  DerivedB
//*/
class DerivedB
  : public virtual Base
{
public:
  DerivedB()
  {
    variable = 2;
  }

  virtual ~DerivedB(){}

  void display_derivedB()
  {
    std::cout << "DerivedB -> Base::variable = " << variable << "\n";
  }
};


/*
  Client
//*/
class Client
  : public DerivedA, public DerivedB
{};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  Client client;
  cout << endl;


  cout << "client.display() - won't compile, call is ambigous!!!\n";
  cout << endl;


  cout << "client.display_derivedA()\n";
  client.display_derivedA();
  cout << endl;


  cout << "cleint.display_derivedB()\n";
  client.display_derivedB();
  cout << endl;


  cout << "READY.\n";
  return 0;
}
