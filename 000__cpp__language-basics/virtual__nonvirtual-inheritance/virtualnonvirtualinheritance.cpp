// nonvirtualinheritance.cpp
/*
  nonvirtual inheritance - in a "diamond" situation, EACH derived class
  will have its own base class.

  +-----------+         +-----------+
  | Base (1)  |         | Base  (2) |
  +-----------+         +-----------+
       /_\                   /_\
        |                     |
        |                     |
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
  virtual ~Base() {}
  void display() { std::cout << "Base::variable = " << variable << "\n"; }
};


/*
  DerivedA
//*/
class DerivedA : public Base
{
public:
  DerivedA() { variable = 1; }

  void display_derivedA()
  {
    std::cout << "DerivedA -> Base::variable = " << variable << "\n";
  }
};


/*
  DerivedB
//*/
class DerivedB : public Base
{
public:
  DerivedB() { variable = 2; }

  void display_derivedB()
  {
    std::cout << "DerivedB -> Base::variable = " << variable << "\n";
  }
};


/*
  Client
//*/
class Client : public DerivedA, public DerivedB
{
};


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
