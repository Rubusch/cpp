// mediator.cpp
/*
  Define an object that encapsulates how a set of objects interact.
  Mediator promotes loose coupling by keeping objects from refering
  to each other explicitly, and it lets you vary their interaction
  independently.

  +---------------------+                      +---------------------+
  | Mediator            |<---------------------| Colleague           |
  +=====================+                      +=====================+
  |                     |                      | pMediator_          |
  +---------------------+                      +---------------------+
  |                     |                      |                     |
  +---------------------+                      +---------------------+
            /_\                                          /_\
             |                                            |
             |                             +--------------+--------------+
             |                             |                             |
  +---------------------+       +---------------------+       +---------------------+
  | ConcreteMediator    |       | ConcreteColleague1  |       | ConcreteColleague2  |
  +=====================+       +=====================+       +=====================+
  |                     |       |                     |       |                     |
  +---------------------+       +---------------------+       +---------------------+
  |                     |------>|                     |    +->|                     |
  +---------------------+       +---------------------+    |  +---------------------+
             |                                             |
             +---------------------------------------------+

  (GoF, 1995)
//*/


#include <iostream>


struct Mediator
{
  virtual ~Mediator() = 0;
};

Mediator::~Mediator() {}


class Collegue
{
protected:
  Mediator* pMediator_;

public:
  virtual void requestSomething() = 0;
  virtual std::string handleSomething() = 0;
  virtual void setMediator(Mediator* mediator)
  {
    pMediator_ = mediator;
  }
};


class ConcreteMediator : public Mediator
{
private:
  Collegue *pCollegue1_;
  Collegue *pCollegue2_;

public:
  ConcreteMediator()
    : pCollegue1_(NULL), pCollegue2_(NULL)
  {}

  std::string askCollegue1()
  {
    if(NULL == pCollegue1_){
      return "failed!";
    }
    return pCollegue1_->handleSomething();
  }

  std::string askCollegue2()
  {
    if(NULL == pCollegue2_){
      return "failed!";
    }
    return pCollegue2_->handleSomething();
  }

  void setCollegue1( Collegue* collegue1)
  {
    pCollegue1_ = collegue1;
  }

  void setCollegue2( Collegue* collegue2)
  {
    pCollegue2_ = collegue2;
  }
};


struct ConcreteCollegue1 : public Collegue
{
  void requestSomething()
  {
    if(NULL == pMediator_) return;
    std::cout << "collegue 1 asks collegue 2 - answer: \""
              << (dynamic_cast< ConcreteMediator* >(pMediator_))->askCollegue2()
              << "\"\n";
  }

  std::string handleSomething()
  {
    return (NULL == pMediator_) ? "FAILED - no mediator set!" : "hello from collegue 1!";
  }
};


struct ConcreteCollegue2 : public Collegue
{
  void requestSomething()
  {
    if(NULL == pMediator_) return;
    std::cout << "collegue 2 asks collegue 1 - answer: \""
              << (dynamic_cast< ConcreteMediator* >(pMediator_))->askCollegue1()
              << "\"\n";
  }

  std::string handleSomething()
  {
    return (NULL == pMediator_) ? "FAILED - no mediator set!" : "collegue 2 says hello!";
  }
};


/*
  main...
//*/
int main()
{
  using namespace std;


  cout << "init\n";
  ConcreteMediator mediator;
  ConcreteCollegue1 collegue1;
  ConcreteCollegue2 collegue2;

  mediator.setCollegue1( &collegue1);
  collegue1.setMediator( &mediator);

  mediator.setCollegue2( &collegue2);
  collegue2.setMediator( &mediator);

  collegue1.requestSomething();
  collegue2.requestSomething();
  cout << endl;


  cout << "READY.\n";
  return 0;
}
