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
  (GoF, 1995)
//*/


#include <iostream>
#include <memory>
#include <string>


struct Product
{
  void setPartA(const std::string& a)
  {
    part_a = a;
  }

  void setPartB(const std::string& b)
  {
    part_b = b;
  }

  void showProduct()
  {
    std::cout << "Product::part_a: \'" << part_a << "\'\n"
              << "Product::part_b: \'" << part_b << "\'\n";
  }

private:
  std::string part_a;
  std::string part_b;
};


struct Builder
{
  std::auto_ptr< Product > getProduct()
  {
    return product_;
  }

  void createNewProduct()
  {
    product_.reset(new Product);
  }

  virtual void buildPartA() = 0;
  virtual void buildPartB() = 0;

protected:
  std::auto_ptr< Product > product_;
};


struct ConcreteBuilderA
  : public Builder
{
  void buildPartA()
  {
    product_->setPartA("TCP");
  }

  void buildPartB()
  {
    product_->setPartB("IP");
  }
};


struct ConcreteBuilderB
  : public Builder
{
  void buildPartA()
  {
    product_->setPartA("UDP");
  }

  void buildPartB()
  {
    product_->setPartB("IP");
  }
};


struct Director
{
  Director()
    : builder_(NULL)
  {}

  ~Director()
  {
    builder_ = NULL;
  }

  void setBuilder(Builder* builder)
  {
    builder_ = builder;
  }

  std::auto_ptr< Product > getProduct()
  {
    return builder_->getProduct();
  }

  void construct()
  {
    builder_->createNewProduct();
    builder_->buildPartA();
    builder_->buildPartB();
  }

private:
  Builder* builder_;
};


/*
  main()
//*/
int main()
{
  using namespace std;

  // init
  Director director;
  std::auto_ptr< Product > product;
  cout << endl;

  // builder A
  ConcreteBuilderA concBuilderA;
  director.setBuilder( &concBuilderA);
  director.construct();
  product = director.getProduct();
  product->showProduct();
  cout << endl;

  // builder B
  ConcreteBuilderB concBuilderB;
  director.setBuilder( &concBuilderB);
  director.construct();
  product = director.getProduct();
  product->showProduct();
  cout << endl;

  cout << "READY.\n";
  return 0;
}
