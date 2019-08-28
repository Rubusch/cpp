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


/*
  Mediator

  - defines an interface for communicating with Collegue objects.
//*/
class Mediator
{
public:
  virtual ~Mediator() = 0;
};

Mediator::~Mediator()
{
  std::cout << "\tMediator::~Mediator()\n";
}


/*
  Collegue

  - each Collegue class knows its Mediator object.
  - each Collegue communicates with its mediator whenever it
  would have otherwise communicated with another Collegue.
//*/
class Collegue
{
protected:
  Mediator* pMediator_;

public:
  // request
  virtual void requestSomething() = 0;

  // answer
  virtual std::string handleSomething() = 0;

  virtual void setMediator(Mediator* mediator)
  {
    std::cout << "\tCollegue::setMediator(Mediator*)\n";
    pMediator_ = mediator;
  }
};


/*
  ConcreteMediator

  - implements cooperative behavior by coordinating Collegue objects.
  - knows and maintains its collegues.
//*/
class ConcreteMediator
  : public Mediator
{
private:
  Collegue *pCollegue1_;
  Collegue *pCollegue2_;

public:
  ConcreteMediator()
    : pCollegue1_(NULL), pCollegue2_(NULL)
  {
    std::cout << "\tConcreteMediator::ConcreteMediator() - ctor\n";
  }

  std::string askCollegue1()
  {
    std::cout << "\tConcreteMediator::askCollegue1()\n";
    if(NULL == pCollegue1_){
      return "failed!";
    }
    return pCollegue1_->handleSomething();
  }

  std::string askCollegue2()
  {
    std::cout << "\tConcreteMediator::askCollegue2()\n";
    if(NULL == pCollegue2_){
      return "failed!";
    }
    return pCollegue2_->handleSomething();
  }

  void setCollegue1( Collegue* collegue1)
  {
    std::cout << "\tConcreteMediator::setCollegue1( ConcreteColleuge1*)\n";
    pCollegue1_ = collegue1;
  }

  void setCollegue2( Collegue* collegue2)
  {
    std::cout << "\tConcreteMediator::setCollegue2( ConcreteCollegue2*)\n";
    pCollegue2_ = collegue2;
  }
};


/*
  Concrete Collegue (1)

  - implements the Collegue interface
//*/
class ConcreteCollegue1
  : public Collegue
{
public:
  void requestSomething()
  {
    std::cout << "\tConcreteCollegue1::requestSomething()\n";
    if(NULL == pMediator_) return;
    std::cout << "collegue 1 asks collegue 2 - answer: \""
              << (dynamic_cast< ConcreteMediator* >(pMediator_))->askCollegue2()
              << "\"\n";
  }

  std::string handleSomething()
  {
    std::cout << "\tConcreteCollegue1::handleSomething()\n";
    return (NULL == pMediator_) ? "FAILED - no mediator set!" : "hello from collegue 1!";
  }
};


/*
  Concrete Collegue (2)

  - implements the Collegue interface
//*/
class ConcreteCollegue2
  : public Collegue
{
public:
  void requestSomething()
  {
    std::cout << "\tConcreteCollegue2::requestSomething()\n";
    if(NULL == pMediator_) return;
    std::cout << "collegue 2 asks collegue 1 - answer: \""
              << (dynamic_cast< ConcreteMediator* >(pMediator_))->askCollegue1()
              << "\"\n";
  }

  std::string handleSomething()
  {
    std::cout << "\tConcreteCollegue2::handleSomething()\n";
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
  cout << endl;

  cout << "register collegue 1\n";
  mediator.setCollegue1( &collegue1);
  collegue1.setMediator( &mediator);
  cout << endl;

  cout << "register collegue 2\n";
  mediator.setCollegue2( &collegue2);
  collegue2.setMediator( &mediator);
  cout << endl;

  cout << "communicate from collegue 1\n";
  collegue1.requestSomething();
  cout << endl;

  cout << "communicate from collegue 2\n";
  collegue2.requestSomething();
  cout << endl;


  cout << "READY.\n";
  return 0;
}
