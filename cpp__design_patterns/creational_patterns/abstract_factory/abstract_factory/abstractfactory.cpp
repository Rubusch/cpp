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
    |         /_\           /_\         +-------------------+   +-------------------+       
    |          |             |          | concrete Factory1 |   | concrete Factory2 |
    |          |             |          +===================+   +===================+
    |          |             |          |                   |   |                   |
    |          |             |          +-------------------+   +-------------------+
    |          |        +-----------+   | createProductA()  |   | createProductA()  |
    |          |        | concrete  |   | createProductB()  |   | createProductB()  |
    |          |        | ProductA2 |   +-------------------+   +-------------------+
    |   +-----------+   +===========+        |         |           |         |      
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
  abstract product A
//*/
struct ProductA{ virtual ~ProductA() = 0; };
ProductA::~ProductA(){}


/*
  concrete product A1
//*/
struct ConcreteProductA1 : public ProductA{};


/*
  concrete product A2
//*/
struct ConcreteProductA2 : public ProductA{};


/*
  abstract product B
//*/
struct ProductB{ virtual ~ProductB() = 0; };
ProductB::~ProductB(){}


/*
  concrete product B1
//*/
struct ConcreteProductB1 : public ProductB{};


/*
  concrete product B2
//*/
struct ConcreteProductB2 : public ProductB{};


/*
  abstract factory
//*/
struct AbstractFactory
{ 
  virtual ProductA* createProductA() = 0;
  virtual ProductB* createProductB() = 0;
};


/*
  factory 1

  instantiate 'concrete product', but pass as 'abstract product'
//*/
struct ConcreteFactory1 : public AbstractFactory
{
  ProductA* createProductA(){ return new ConcreteProductA1(); }
  ProductB* createProductB(){ return new ConcreteProductB1(); }
};


/*
  factory 2

  instantiate 'concrete product', but pass as 'abstract product'
//*/
struct ConcreteFactory2 : public AbstractFactory
{
  ProductA* createProductA(){ return new ConcreteProductA2(); }
  ProductB* createProductB(){ return new ConcreteProductB2(); }
};


/*
  main()..
//*/
int main()
{
  // init
  ConcreteFactory1 *pConcFactory1 = NULL;
  ConcreteFactory2 *pConcFactory2 = NULL;


  // alloc
  pConcFactory1 = new ConcreteFactory1();
  pConcFactory2 = new ConcreteFactory2();


  // usage of the factory 1
  ConcreteProductA1 *pConcProductA1 = dynamic_cast< ConcreteProductA1* >(pConcFactory1->createProductA());
  ConcreteProductB1 *pConcProductB1 = dynamic_cast< ConcreteProductB1* >(pConcFactory1->createProductB());


  // usage of the factory 2
  ConcreteProductA2 *pConcProductA2 = dynamic_cast< ConcreteProductA2* >(pConcFactory2->createProductA());
  ConcreteProductB2 *pConcProductB2 = dynamic_cast< ConcreteProductB2* >(pConcFactory2->createProductB());


  // delete
  delete pConcFactory1; pConcFactory1 = NULL;
  delete pConcFactory2; pConcFactory2 = NULL;
  delete pConcProductA1; pConcProductA1 = NULL;
  delete pConcProductB1; pConcProductB1 = NULL;
  delete pConcProductA2; pConcProductA2 = NULL;
  delete pConcProductB2; pConcProductB2 = NULL;  


  return 0;
}
