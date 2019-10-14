// factorymethod.cpp
/*
  Define an interface for creating an object, but let the subclasses decide
  which class to instantiate. The factory method lets a class defer
  instantiation to its subclasses.

  +---------------------+                      +---------------------+
  | Product             |                      | Creator             |
  +=====================+                      +=====================+
  |                     |                      |                     |
  +---------------------+                      +---------------------+
  |                     |                      | factoryMethod()     |
  +---------------------+                      |  : Product          |
            /_\                                +---------------------+
             |                                           /_\
             |                                            |
             |                                            |
             |                                            |
  +---------------------+                      +---------------------+
  | ConcreteProduct     |                      | ConcreteCreator     |
  +=====================+                      +=====================+
  |                     |<- - - - - - - - - - -|                     |
  +---------------------+                      +---------------------+
  |                     |                      | factoryMethod()     |
  +---------------------+                      |  : Product          |
                                               +-------------|-------+

                                                             |

                                                             |
                                     +------------------------------+\
                                     | return new ConcreteProduct   +-+
                                     +--------------------------------+


  (GoF, 1995)

  The Product in the below example could also consist of two different classes
  and not only two different constructors.
//*/

#include <iostream>


class Product
{
public:
  virtual ~Product() {}
};


class ConcreteProduct : public Product
{
public:
  ConcreteProduct(std::string str)
  {
    std::cout << "\t\tProduct::Product(std::string) - instantiated with \'"
              << str << "\'\n";
  }

  ConcreteProduct(int cnt)
  {
    std::cout << "\t\tProduct::Product(int) - instantiated with \'" << cnt
              << "\'\n";
  }
};


class Creator
{
public:
  virtual ~Creator() {}
  virtual Product *factoryMethod() = 0;
};


struct ConcreteCreator1 : public Creator {
  Product *factoryMethod() { return new ConcreteProduct("abc"); }
};


struct ConcreteCreator2 : public Creator {
  Product *factoryMethod() { return new ConcreteProduct(123); }
};


/*
  main...
//*/
int main()
{
  using namespace std;

  // init
  cout << "init...\n";
  Product *ptr1 = NULL;
  Product *ptr2 = NULL;
  ConcreteCreator1 *pConcCreator1 = new ConcreteCreator1();
  ConcreteCreator2 *pConcCreator2 = new ConcreteCreator2();
  cout << endl;


  // usage
  cout << "...use of the factory method\n";

  cout << "creator 1:\n";
  ptr1 = pConcCreator1->factoryMethod();

  cout << "creator 2:\n";
  ptr2 = pConcCreator2->factoryMethod();
  cout << endl;


  // free
  cout << "free...\n";
  delete ptr1;
  ptr1 = NULL;
  delete ptr2;
  ptr2 = NULL;
  delete pConcCreator1;
  pConcCreator1 = NULL;
  delete pConcCreator2;
  pConcCreator2 = NULL;
  cout << endl;


  cout << "READY.\n";
  return 0;
}
