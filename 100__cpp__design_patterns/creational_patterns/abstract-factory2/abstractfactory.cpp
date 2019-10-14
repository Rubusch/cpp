// abstractfactory.cpp
/*
  Provide an interface for creating families of related or dependent
  objects without specifying their concrete classes.


  +--------+                                        +---------------------+
  | Client |--------------------------------------->| abstract Factory    |
  +--------+                                        +=====================+
    |  |                                            |                     |
    |  |                                            +---------------------+
    |  |   +---------------------+                  | createProductA()    |
    |  +-->| abstract Product A  |                  | createProductB()    |
    |      +=====================+                  +---------------------+
    |      |                     |                     /_\           /_\
    |      +---------------------+                      |             |
    |      |                     |                  +---+             +---+
    |      +---------------------+                  |                     |
    |         /_\           /_\         +-------------------+
+-------------------+ |          |             |          | concrete Factory1 |
| concrete Factory2 | |          |             |          +===================+
+===================+ |          |             |          |                   |
|                   | |          |             |          +-------------------+
+-------------------+ |          |        +-----------+   | createProductA()  |
| createProductA()  | |          |        | concrete  |   | createProductB()  |
| createProductB()  | |          |        | ProductA2 |   +-------------------+
+-------------------+ |   +-----------+   +===========+        |         | | |
    |   | concrete  |   |           |<-------|---------|-----------+         |
    |   | ProductA1 |   +-----------+        |         |                     |
    |   +===========+                        |         |                     |
    |   |           |<-----------------------+         |                     |
    |   +-----------+                                  |                     |
    |                                                  |                     |
    |                                                  |                     |
    |                                                  |                     |
    |      +---------------------+                     |                     |
    +----->| abstract Product B  |                     |                     |
           +=====================+                     |                     |
           |                     |                     |                     |
           +---------------------+                     |                     |
           |                     |                     |                     |
           +---------------------+                     |                     |
               /_\           /_\                       |                     |
                |             |                        |                     |
                |             |                        |                     |
                |             |                        |                     |
                |       +-----------+                  |                     |
                |       | concrete  |                  |                     |
                |       | ProductB2 |                  |                     |
        +-----------+   +===========+                  |                     |
        | concrete  |   |           |<-----------------|---------------------+
        | ProductB1 |   +-----------+                  |
        +===========+                                  |
        |           |<---------------------------------+
        +-----------+

  (GoF, 1995)


  Use dynamic_cast<>() when downcasting!
//*/


#include <iostream>


/*
  Abstract Product A

  - declares an interface for a type of product object
//*/
class ProductA
{
public:
  ProductA() { std::cout << "\t\t\tProductA::ProductA() - ctor\n"; }

  virtual ~ProductA() = 0;
};

ProductA::~ProductA() { std::cout << "\t\t\tProductA::~Product() - dtor\n"; }


/*
  Concrete Product A1

  - defines a product object to be created by the corresponding concrete factory
  - implements the AbstractProduct interface
//*/
class ConcreteProductA1 : public ProductA
{
public:
  ConcreteProductA1()
  {
    std::cout << "\t\tConcreteProductA1::ConcreteProductA1() - ctor\n";
  }

  ~ConcreteProductA1()
  {
    std::cout << "\t\tConcreteProductA1::~ConcreteProductA1() - dtor\n";
  }
};


/*
  Concrete Product A2 - another type of a concrete product
//*/
class ConcreteProductA2 : public ProductA
{
public:
  ConcreteProductA2()
  {
    std::cout << "\t\tConcreteProductA2::ConcreteProductA2() - ctor\n";
  }

  ~ConcreteProductA2()
  {
    std::cout << "\t\tConcreteProductA2::~ConcreteProductA2() - dtor\n";
  }
};


/*
  Abstract Product B - another type of product
//*/
class ProductB
{
public:
  ProductB() { std::cout << "\t\t\tProductB::ProductB() - ctor\n"; }

  virtual ~ProductB() = 0;
};

ProductB::~ProductB() { std::cout << "\t\t\tProductB::~ProductB() - dtor\n"; }


/*
  Concrete Product B1 - another type of a concrete product
//*/
class ConcreteProductB1 : public ProductB
{
public:
  ConcreteProductB1()
  {
    std::cout << "\t\tConcreteProductB1::ConcreteProductB1() - ctor\n";
  }

  ~ConcreteProductB1()
  {
    std::cout << "\t\tConcreteProductB1::~ConcreteProductB1() - dtor\n";
  }
};


/*
  Concrete Product B2 - another type of a concrete product
//*/
class ConcreteProductB2 : public ProductB
{
public:
  ConcreteProductB2()
  {
    std::cout << "\t\tConcreteProductB2::ConcreteProductB2() - ctor\n";
  }

  ~ConcreteProductB2()
  {
    std::cout << "\t\tConcreteProductB2::~ConcreteProductB2() - dtor\n";
  }
};


/*
  Abstract Factory

  - declares an interface for operations that create abstract product objects
//*/
class AbstractFactory
{
public:
  virtual ~AbstractFactory() {}
  virtual ProductA *createProductA() = 0;
  virtual ProductB *createProductB() = 0;
};


/*
  Concrete Factory 1

  - instantiate 'concrete product', but pass as 'abstract product'
  - implements the operations to create concrete product objects
//*/
class ConcreteFactory1 : public AbstractFactory
{
public:
  ProductA *createProductA()
  {
    std::cout << "\tConcreteFactory1::createProductA()\n";
    return new ConcreteProductA1();
  }

  ProductB *createProductB()
  {
    std::cout << "\tConcreteFactory1::createProductB1()\n";
    return new ConcreteProductB1();
  }
};


/*
  Concrete Factory 2 - another concrete factory
//*/
class ConcreteFactory2 : public AbstractFactory
{
public:
  ProductA *createProductA()
  {
    std::cout << "\tConcreteFactory2::createProductA()\n";
    return new ConcreteProductA2();
  }

  ProductB *createProductB()
  {
    std::cout << "\tConcreteFactory2::createProductB()\n";
    return new ConcreteProductB2();
  }
};


/*
  main()..
//*/
int main()
{
  using namespace std;

  // init
  cout << "init..\n";
  ConcreteFactory1 *pConcFactory1 = NULL;
  ConcreteFactory2 *pConcFactory2 = NULL;
  cout << endl;

  // alloc
  cout << "allocate..\n";
  pConcFactory1 = new ConcreteFactory1();
  pConcFactory2 = new ConcreteFactory2();
  cout << endl;

  // usage of the factory 1
  cout << "...use factory 1\n";

  cout << "\'product A\':\n";
  ConcreteProductA1 *pConcProductA1 =
      dynamic_cast< ConcreteProductA1 * >(pConcFactory1->createProductA());

  cout << "\'product B\':\n";
  ConcreteProductB1 *pConcProductB1 =
      dynamic_cast< ConcreteProductB1 * >(pConcFactory1->createProductB());
  cout << endl;

  // usage of the factory 2
  cout << "...use factory 2\n";

  cout << "\'product A\':\n";
  ConcreteProductA2 *pConcProductA2 =
      dynamic_cast< ConcreteProductA2 * >(pConcFactory2->createProductA());

  cout << "\'product B\':\n";
  ConcreteProductB2 *pConcProductB2 =
      dynamic_cast< ConcreteProductB2 * >(pConcFactory2->createProductB());
  cout << endl;

  // delete
  cout << "free..\n";
  delete pConcFactory1;
  pConcFactory1 = NULL;
  delete pConcFactory2;
  pConcFactory2 = NULL;
  delete pConcProductA1;
  pConcProductA1 = NULL;
  delete pConcProductB1;
  pConcProductB1 = NULL;
  delete pConcProductA2;
  pConcProductA2 = NULL;
  delete pConcProductB2;
  pConcProductB2 = NULL;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
