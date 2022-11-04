// bridge.cpp
/*
  Decouple an abstraction from its implementation so that the two can vary
independently.

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
*/


#include <iostream>


class Implementor
{
protected:
  std::string data;

public:
  Implementor() : data("empty") {}

  virtual ~Implementor() {}

  virtual void functionImpl() = 0;

  std::string getData() const { return data; }
};


class ConcreteImplementor : public Implementor
{
public:
  void functionImpl()
  {
    data = "bridge worked out and this string has been set!";
  }
};


class Concept
{
protected:
  Implementor *pImplementor_;

public:
  Concept(Implementor &implementor) : pImplementor_(&implementor) {}

  virtual ~Concept() {}
  virtual void function() = 0;
  virtual void show()
  {
    std::cout << "\n-> data: \'" << pImplementor_->getData() << "\'\n";
  }
};


class ConcreteConcept : public Concept
{
public:
  ConcreteConcept(Implementor &implementor) : Concept(implementor) {}

  void function()
  {
    ConcreteImplementor *pConcImpl = NULL;
    pConcImpl = static_cast< ConcreteImplementor * >(pImplementor_);
    pConcImpl->functionImpl();

    show();
  }
};


/*
  main..
*/
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
