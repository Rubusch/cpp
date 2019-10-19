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
                     |     not obligatory                |
                     +------------------+                |
                     |                  |                |
   +---------------------+   +---------------------+     |
   | ConcreteComponent   |   | Decorator           |     |
   +=====================+   +=====================+     |
   |                     |   | pComp : Component*  |<>---+
   +---------------------+   +---------------------+ +--------------------+\ |
operation()         |   | operation() - - - - - - - - - - - - -|
pComp->Operation() +-+
   +---------------------+   +---------------------+ +----------------------+
                                       /_\
                                        |
                           +------------+------------+
                           |                         |
                +---------------------+   +---------------------+
                | ConcreteDecoratorA  |   | ConcreteDecoratorB  |
                +=====================+   +=====================+
                | addedState          |   |                     |
                +---------------------+   +---------------------+
+-------------------------+\ | operation()         |   | operation()         |
| Decorator::operation(); +-+
                +---------------------+   | addedBehavior() - - - - |
addedBehavior();          |
                                          +---------------------+
+---------------------------+

   (GoF, 1995)
//*/


#include <iostream>


struct Component {
  virtual ~Component() {}
  virtual void operation() = 0; // will NEVER be called -> abstract class!

  void commonOperation()
  {
    std::cout << "> test of an inherited base functionalty!\n";
  }
};


struct ConcreteComponent : public Component {
  void operation()
  {
    std::cout << "> ConcreteComponent was operation called!\n";
  }
};


struct Decorator : public Component {
  Decorator(Component &component) : pComponent_(&component) {}

  void operation() { pComponent_->operation(); }

private:
  Component *pComponent_;
};


struct ConcreteDecoratorA : public Decorator {
  ConcreteDecoratorA(Component &component) : Decorator(component), addedState(7)
  {
    std::cout << "> addedState = " << addedState << "\n";
  }

  void operation() { Decorator::operation(); }

private:
  int addedState;
};


struct ConcreteDecoratorB : public Decorator {
  ConcreteDecoratorB(Component &component) : Decorator(component) {}

  void operation() { Decorator::operation(); }

  void addedBehavior()
  {
    std::cout << "> some new operation of the ConcreteDecoratorB object.\n";
  }
};


/*
  main..
//*/
int main()
{
  ConcreteComponent concComp;


  ConcreteDecoratorA concDecoratorA(concComp);
  concDecoratorA.operation();
  concDecoratorA.commonOperation();


  ConcreteDecoratorB concDecoratorB(concComp);
  concDecoratorB.addedBehavior();
  concDecoratorB.operation();
  concDecoratorB.commonOperation();


  return 0;
}
