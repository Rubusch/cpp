// bridge.cpp
/*
  Decouple an abstraction from its implementation so that the two can vary independently.

  +---------------------+                       +---------------------+
  | Concept             |<>-------------------->| Implementor         |
  +=====================+                       +=====================+
  | impl: Implementor   |                       |                     |
  +---------------------+                       +---------------------+
  | function()          |                       | functionimpl()      |
  +-----------------|---+                       +---------------------+
           /_\                                            /_\
            |       |   +-----------------------------+    |
            |           | this->impl.functionImpl()   |\   |      
            |       +- -+                             +-+  |
            |           +-------------------------------+  |
            |                                              |
  +---------------------+                       +---------------------+
  | ConcreteConcept     |                       | ConcreteImplementor |
  +=====================+                       +=====================+
  |                     |                       |                     |
  +---------------------+                       +---------------------+
  | function()          |                       | functionImpl()      |
  +---------------------+                       +---------------------+

  (GoF, 1995)
//*/


#include <iostream>


/*
  Implementor

  - defines the interface for implementation classes. This interface doesn't have to 
  correspond exactly to Abstraction's interface; in fact the two interfaces can be 
  quite different. Typically the Implementor interface provides only primitive 
  operations, and Abstraction defines higher-level operations based on these primitives.
//*/
class Implementor
{
protected: 
  std::string data;

public:
  Implementor()
    : data("empty")
  {}

  // abstract implementation body
  virtual void functionImpl() = 0;

  std::string getData() const
  {
    return data;
  }
};


/*
  Concrete Implementor
  
  - implements the Implementor interface and defines its concrete impelementation
//*/
class ConcreteImplementor
  : public Implementor
{
public:
  // implementation
  void functionImpl()
  {
    std::cout << "\t\tConcreteImplmentor::functionImpl()\n";
    data = "bridge worked out and this string has been set!";
  }
};


/*
  Concept Abstraction

  - defines the abstraction's interface
  - maintains a reference to an object of type Implementor
//*/
class Concept
{
protected:
  Implementor *pImplementor_;

public:
  Concept( Implementor& implementor)
    :pImplementor_(&implementor)
  {}

  virtual void function() = 0;
 
  virtual void show()
  {
    std::cout << "\n-> data: \'" << pImplementor_->getData() << "\'\n";
  }
};


/*
  Concrete Concept Class
  
  - Extends the interface defined by Abstraction
//*/
class ConcreteConcept
  : public Concept
{
public:
  ConcreteConcept( Implementor& implementor) 
    : Concept(implementor)
  {}

  void function()
  {
    std::cout << "\tConcreteConcept::function()\n";

    ConcreteImplementor* pConcImpl = NULL;

    pConcImpl = static_cast< ConcreteImplementor* >(pImplementor_);

    pConcImpl->functionImpl();

    // show result
    show();
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  ConcreteImplementor concImplementor;
  ConcreteConcept concConcept(concImplementor);
  cout << endl;

  cout << "call function:\n";
  concConcept.function();
  cout << endl;

  cout << "READY.\n";
  return 0;
}
