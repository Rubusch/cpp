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
       |                                              /_\
       |                                               |
       |                                +--------------+--------------+
       |                                |                             |
       |                     +---------------------+       +---------------------+
       |                     | ConcreteFlyweight   |       | Unshared            |
       |                  +->|                     |    +->|   ConcreteFlyweight |
       |                  |  +=====================+    |  +=====================+
       |                  |  |                     |    |  |                     |
       |                  |  +---------------------+    |  +---------------------+
       |                  |  | operation(          |    |  | operation(          |
       |                  |  |   intrinsic state)  |    |  |   intrinsic state)  |
       |                  |  +---------------------+    |  +---------------------+
       |                  |                             |
       |                  |                             |
  +--------+              |                             |
  | client |--------------+-----------------------------+
  +--------+

  (GoF, 1995)
*/


#include <iostream>


struct Flyweight {
  virtual ~Flyweight() {}
  virtual void operation() = 0;
};


struct SharedConcreteFlyweight : public Flyweight {
  SharedConcreteFlyweight(std::string &str) : pStr_(&str) {}

  void operation() { std::cout << "operation - *pStr_ = " << *pStr_ << "\n"; }

private:
  std::string *pStr_;
};


struct UnsharedConcreteFlyweight : public Flyweight {
  UnsharedConcreteFlyweight(std::string &str, unsigned int &num)
      : str_(str), num_(num)
  {
  }

  void operation()
  {
    std::cout << "operation - str_ = " << str_ << ", "
              << "num_ = " << num_ << "\n";
  }

private:
  std::string str_;
  unsigned int num_;
};


struct FlyweightFactory {
  FlyweightFactory()
  {
    str_ = "Hello World!";
    num_ = 777;
  }

  Flyweight &getSharedFlyweight()
  {
    pFlyweight = new SharedConcreteFlyweight(str_);
    return *pFlyweight;
  }

  Flyweight &getUnsharedFlyweight()
  {
    pFlyweight = new UnsharedConcreteFlyweight(str_, num_);
    return *pFlyweight;
  }

private:
  std::string str_;
  unsigned int num_;

  Flyweight *pFlyweight;
};


/*
  main..
*/
int main()
{
  using namespace std;

  FlyweightFactory factory;
  cout << endl;


  Flyweight *pFly_1 = &(factory.getSharedFlyweight());
  pFly_1->operation();
  cout << endl;


  Flyweight *pFly_2 = &(factory.getUnsharedFlyweight());
  pFly_2->operation();
  cout << endl;


  std::cout << "READY.\n";
  return 0;
}
