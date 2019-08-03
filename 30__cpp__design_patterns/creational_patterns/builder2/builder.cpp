// builder.cpp
/*
  Separate the construction of a complex object from its representation so
  that the same construction process can create different representations.

  +---------------------+                       +---------------------+
  | Director            |                       | Builder             |
  +=====================+                       +=====================+
  |                     |---------------------->|                     |
  +---------------------+                       +---------------------+
  | construct()         |                       | buildPart()         |
  +-----------------|---+                       +---------------------+
                                                          /_\
                    |                                      |
                                                           |
                    |                                      |
  +---------------------+                       +---------------------+           +-----------+
  | For all objects in  |\                      | ConcreteBuilder     |- - - - - >| Product   |
  | structure           | \                     +=====================+           +===========+
  | {                   +--+                    |                     |           |           |
  |   builder->buildPart() |                    +---------------------+           +-----------+
  | }                      |                    | buildPart()         |
  +------------------------+                    | getResult()         |
                                                +---------------------+

  Collaboration:

  - The client creates the Director object and configures it with the desired Buidler object
  - Director notifies the builder whenever a part of the product should be built
  - Builder handles requests from the director and adds parts to the product
  - The client retrieves the product from the builder

  (GoF, 1995)
//*/


#include <iostream>
#include <memory>
#include <string>


/*
  Product

  - represents the complex object under construction. ConcreteBuilder builds the
  product's internal representation and defines the process by which it's assembled
  - includes classes that define the constituent parts, including interfaces for
  assembling the parts into the final result
//*/
class Product
{
private:
  std::string part_a;
  std::string part_b;

public:
  Product()
  {
    std::cout << "\t\t\tProduct::Product() - ctor\n";
  }

  ~Product()
  {
    std::cout << "\t\t\tProduct::~Product() - dtor\n";
  }

  void setPartA(const std::string& a)
  {
    std::cout << "\t\t\tProduct::setPartA()\n";
    part_a = a;
  }

  void setPartB(const std::string& b)
  {
    std::cout << "\t\t\tProduct::setPartB()\n";
    part_b = b;
  }

  void showProduct()
  {
    std::cout << "\t\t\tProduct::part_a: \'" << part_a << "\'\n"
              << "\t\t\tProduct::part_b: \'" << part_b << "\'\n";
  }
};


/*
  Builder (abstract)

  - specifies an abstract interface for creating parts of a Product object
//*/
class Builder
{
protected:
  std::auto_ptr< Product > product_;

public:
  Builder()
  {
    std::cout << "\t\tBuilder::Builder() - ctor\n";
  }

  virtual ~Builder()
  {
    std::cout << "\t\tBuilder::~Builder() - dtor\n";
  }

  std::auto_ptr< Product > getProduct()
  {
    std::cout << "\t\tBuilder::getProduct()\n";
    return product_;
  }

  void createNewProduct()
  {
    std::cout << "\t\tBuilder::createNewProduct()\n";
    product_.reset(new Product);
  }

  virtual void buildPartA() = 0;
  virtual void buildPartB() = 0;
};


/*
  Concrete Builder A

  - constructs and assembles parts of the product by implementing the Builder interface
  - defines and keeps track of the representation it creates
  - provides an interface for retrieving the product
//*/
class ConcreteBuilderA
  : public Builder
{
public:
  ConcreteBuilderA()
  {
    std::cout << "\t\tConcreteBuilderA::ConcreteBuilderA() - ctor\n";
  }

  ~ConcreteBuilderA()
  {
    std::cout << "\t\tConcreteBuilderA::~ConcreteBuilderA() - dtor\n";
  }

  void buildPartA()
  {
    std::cout << "\t\tConcreteBuilderA::buildPartA()\n";
    product_->setPartA("TCP");
  }

  void buildPartB()
  {
    std::cout << "\t\tConcreteBuilderA::buildPartB()\n";
    product_->setPartB("IP");
  }
};


/*
  Concrete Builder B - another Concrete Builder type
//*/
class ConcreteBuilderB
  : public Builder
{
public:
  ConcreteBuilderB()
  {
    std::cout << "\t\tConcreteBuilderB::ConcreteBuilderB() - ctor\n";
  }

  ~ConcreteBuilderB()
  {
    std::cout << "\t\tConcreteBuilderB::~ConcreteBuilderB() - dtor\n";
  }

  void buildPartA()
  {
    std::cout << "\t\tConcreteBuilderB::buildPartA()\n";
    product_->setPartA("UDP");
  }

  void buildPartB()
  {
    std::cout << "\t\tConcreteBuilderB::buildPartB()\n";
    product_->setPartB("IP");
  }
};


/*
  Director

  - constructs an object using the Builder interface
//*/
class Director
{
private:
  Builder* builder_;

public:
  Director()
    :builder_(NULL)
  {
    std::cout << "\tDirector::Director() - ctor\n";
  }

  ~Director()
  {
    std::cout << "\tDirector::~Director() - dtor\n";
    builder_ = NULL;
  }

  void setBuilder(Builder* builder)
  {
    std::cout << "\tDirector::setBuilder()\n";
    builder_ = builder;
  }

  std::auto_ptr< Product > getProduct()
  {
    std::cout << "\tDirector::getProduct()\n";
    return builder_->getProduct();
  }

  void construct()
  {
    std::cout << "\tDirector::construct()\n";
    builder_->createNewProduct();
    builder_->buildPartA();
    builder_->buildPartB();
  }
};


/*
  main()
//*/
int main()
{
  using namespace std;

  // init
  cout << "init..\n";
  Director director;
  std::auto_ptr< Product > product;
  cout << endl;

  // builder A
  cout << "builder A\n";
  ConcreteBuilderA concBuilderA;
  director.setBuilder( &concBuilderA);
  director.construct();
  product = director.getProduct();
  product->showProduct();
  cout << endl;

  // builder B
  cout << "builder B\n";
  ConcreteBuilderB concBuilderB;
  director.setBuilder( &concBuilderB);
  director.construct();
  product = director.getProduct();
  product->showProduct();
  cout << endl;

  cout << "READY.\n";
  return 0;
}