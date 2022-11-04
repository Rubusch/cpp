// flyweight.cpp
/*
  Use sharing to support large numbers of fine-grained objects efficiently.

             +---------------------+        +---------------------+
       +---->| FlyweightFactory    |<>----->| Flyweight           |
       |     +=====================+  pool  +=====================+
       |     |                     |        |                     |
       |     +---------------------+        +---------------------+
       |     | getFlyweight(key)   |        | operation(          |
       |     +---------------------+        |    intrinsic state) |
       |                                    +---------------------+
       |                                           /_\
       |                                            |
       |                             +--------------+--------------+
       |                             |                             |
       |                  +---------------------+       +---------------------+
       |                  | ConcreteFlyweight   |       | Unshared            |
       |               +->|                     |    +->|   ConcreteFlyweight |
       |               |  +=====================+    |  +=====================+
       |               |  |                     |    |  |                     |
       |               |  +---------------------+    |  +---------------------+
       |               |  | operation(          |    |  | operation(          |
       |               |  |   intrinsic state)  |    |  |   intrinsic state)  |
       |               |  +---------------------+    |  +---------------------+
       |               |                             |
       |               |                             |
  +--------+           |                             |
  | client |-----------+-----------------------------+
  +--------+

  (GoF, 1995)
*/


#include <iostream>
#include <memory>
#include <utility>


/*
  Flyweight

  - declares an interface through which flyweights can receive and act on
  extrinsic state
*/
class Flyweight
{
public:
  virtual ~Flyweight() = default;
  virtual void operation() = 0;
};


/*
  Shared Concrete Flyweight

  - implements the Flyweight interface and adds storage for intrinsic state,
  if any. A ConcreteFlyweight object must be sharable. Any state it stores
  must be intrinsic; that is, it must be independent of the ConcreteFlyweight
  object's context.
//*/
class SharedConcreteFlyweight : public Flyweight
{
private:
  const std::string *pStr_;

public:
  SharedConcreteFlyweight(const std::string &str) : pStr_(&str)
  {
    std::cout << "\tSharedConcreteFlyweight::SharedConcreteFlyweight(std::"
                 "string &str) - ctor\n";
  }

  void operation()
  {
    std::cout << "\tSharedConcreteFlyweight::operation()\n";
    std::cout << "operation - *pStr_ = " << *pStr_ << "\n";
  }
};


/*
  Unshared Concrete Flyweight

  - not all Flyweight subclass need to be shared. The Flyweight interface
enables sharing; it doesn't enforce it. It's common for
UnsharedConcreteFlyweight objects to have CocnreteFlyweight objects as children
at some level in the flyweight object structure (as the Row and Column classes
have).
*/
class UnsharedConcreteFlyweight : public Flyweight
{
private:
  const std::string str_;
  unsigned int num_;

public:
  UnsharedConcreteFlyweight(std::string str, const unsigned int &num)
      : str_(std::move(str)), num_(num)
  {
    std::cout << "\tUnsharedConcreteFlyweight::UnsharedConcreteFlyweight(std::"
                 "string& str, unsigned int& number) - ctor\n";
  }

  void operation()
  {
    std::cout << "\tUnsharedConcreteFlyweight::operation()\n";
    std::cout << "operation - str_ = " << str_ << ", "
              << "num_ = " << num_ << "\n";
  }
};


/*
  Flyweight Factory

  - creates and manages flyweight objects
  - ensures that flyweights are shared properly. When a client requests a
flyweight, the FlyweightFactory object supplies an existing instance or creates
one, if none exists.
*/
class FlyweightFactory
{
private:
  std::string str_;
  unsigned int num_;
  std::shared_ptr< Flyweight > pFlyweight;

public:
  FlyweightFactory()
  {
    std::cout << "\tFlyweightFactory::FlyweightFactory() - ctor\n";
    str_ = "Hello World!";
    num_ = 777;
  }

  std::shared_ptr< Flyweight > getSharedFlyweight()
  {
    std::cout << "\tFlyweightFactory::getSharedFlyweight()\n";
    pFlyweight = std::make_shared< SharedConcreteFlyweight >(str_);
    return pFlyweight;
  }

  std::shared_ptr< Flyweight > getUnsharedFlyweight()
  {
    std::cout << "\tFlyweightFactory::getUnsharedFlyweight()\n";
    pFlyweight = std::make_shared< UnsharedConcreteFlyweight >(str_, num_);
    return pFlyweight;
  }
};


/*
  client - main..

  - maintains a reference to flyweight(s).
  - computes or stores the extrinsic state of flyweight(s)
*/
int main()
{
  using namespace std;

  cout << "init\n";
  FlyweightFactory factory;
  cout << endl;


  cout << "get concrete shared flyweight..\n";
  auto pFly_1 = factory.getSharedFlyweight();
  pFly_1->operation();
  cout << endl;


  cout << "get unshared concrete flyweight..\n";
  auto pFly_2 = factory.getUnsharedFlyweight();
  pFly_2->operation();
  cout << endl;


  std::cout << "READY.\n";
  return 0;
}
