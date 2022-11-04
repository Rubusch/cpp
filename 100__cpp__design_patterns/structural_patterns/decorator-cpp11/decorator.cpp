// decorator.cpp
/*
   Attach additional responsabilities to an object dynamically. Decorators
   provide a flexible alternative to subclassing for extending funcitonality.

                +---------------------+
                | Component           |
                +=====================+
                |                     |------------------+
                +---------------------+                  |
                | virtual operation() |                  |
                +---------------------+                  |
                    /_\                                  |
                     | for public and protected          |
                     +------------------+ attributes     |
                     |   (not obligated)|                |
   +---------------------+   +---------------------+     |
   | ConcreteComponent   |   | Decorator           |     |
   +=====================+   +=====================+     |
   |                     |   | pComp : Component*  |<>---+
   +---------------------+   +---------------------+                +--------------------+\
   | operation()         |   | operation() - - - - - - - - - - - - -| pComp->Operation() +-+
   +---------------------+   +---------------------+                +----------------------+
                                       /_\
                                        |
                           +------------+------------+
                           |                         |
                +---------------------+   +---------------------+
                | ConcreteDecoratorA  |   | ConcreteDecoratorB  |
                +=====================+   +=====================+
                | addedState          |   |                     |
                +---------------------+   +---------------------+   +-------------------------+\
                | operation()         |   | operation()         |   | Decorator::operation(); +-+
                +---------------------+   | addedBehavior() - - - - | addedBehavior();          |
                                          +---------------------+   +---------------------------+

   (GoF, 1995)
*/


#include <iostream>


/*
  Component

  - defines the interface for objects that can have responsibilities added
  to them dynamically
*/
class Component
{
public:
  virtual ~Component() = default;
  virtual void operation() = 0; // will NEVER be called -> abstract class!
  void commonOperation()
  {
    std::cout << "> test of an inherited base functionalty!\n";
  }
};


/*
  ConcreteComponent

  - defines an object to which additional responsibilities can be attached
*/
class ConcreteComponent : public Component
{
public:
  void operation()
  {
    std::cout << "\tConcreteComponent::operation()\n";
    std::cout << "> ConcreteComponent was operation called!\n";
  }
};


/*
  Decorator

  - maintains a reference to a Component object and defines an interface that
  conforms to Component's interface
*/
class Decorator : public Component
{
private:
  Component *pComponent_;

public:
  Decorator(Component &component) : pComponent_(&component)
  {
    std::cout << "\tDecorator::Decorator() - ctor\n";
  }

  void operation()
  {
    std::cout << "\tDecorator::operation()\n";
    pComponent_->operation();
  }
};


/*
  ConcreteDecoratorA

  - adds responsibilities to the component
*/
class ConcreteDecoratorA : public Decorator
{
private:
  int addedState;

public:
  ConcreteDecoratorA(Component &component) : Decorator(component), addedState(7)
  {
    std::cout << "\tConcreteDecoratorA::ConcreteDecoratorA(Component const&) - "
                 "ctor\n";
    std::cout << "> addedState = " << addedState << "\n";
  }

  void operation()
  {
    std::cout << "\tConcreteDecoratorA::operation()\n";
    Decorator::operation();
  }
};


/*
  ConcreteDecoratorB - another Concrete Decorator
*/
class ConcreteDecoratorB : public Decorator
{
public:
  ConcreteDecoratorB(Component &component) : Decorator(component)
  {
    std::cout
        << "\tConcreteDecoratorB::concreteDecorator(Component const&) - ctor\n";
  }

  void operation()
  {
    std::cout << "\tConcreteDecoratorB::operation()\n";
    Decorator::operation();
  }

  void addedBehavior()
  {
    std::cout << "\tConcreteDecoratorB::addedBehavior()\n";
    std::cout << "> some new operation of the ConcreteDecoratorB object.\n";
  }
};


/*
  main..
*/
int main()
{
  using namespace std;

  cout << "init..\n";
  ConcreteComponent concComp;
  cout << endl;

  cout << "\n*** decorator A ***\n\n\n";

  cout << "add new state variable to the ConcreteComponent's instance "
          "dynamically:\n";
  ConcreteDecoratorA concDecoratorA(concComp);
  cout << endl;

  cout << "call operation()\n";
  concDecoratorA.operation();
  cout << endl;

  cout << "\n*** decorator B ***\n\n\n";

  cout
      << "add new behaviour to the ConcreteComponent's instance dynamically:\n";
  ConcreteDecoratorB concDecoratorB(concComp);
  cout << endl;

  cout << "call the added operation\n";
  concDecoratorB.addedBehavior();
  cout << endl;

  cout << "call operation()\n";
  concDecoratorB.operation();
  cout << endl;

  cout << "\n*** common functionality ***\n\n\n";

  cout << "call a the commonly inherited operation\n";
  concDecoratorA.commonOperation();
  concDecoratorB.commonOperation();
  cout << endl;

  cout << "READY.\n";
  return 0;
}
