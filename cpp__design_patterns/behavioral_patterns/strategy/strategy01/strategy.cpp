// strategy.cpp
/*
  Define a family of algorithms, encapsulate each one, and make them interchangeble.
  Strategy lets the algorithm vary independently from clients that use it.

  +---------------------+                     +-----------------------+    
  | Context             |<>------------------>| Strategy              |
  +=====================+                     +=======================+
  |                     |                     |                       |
  +---------------------+                     +-----------------------+    
  | contextInterface()  |                     | algorithm()           |
  +-|-------------------+                     +-----------------------+
    |                                                    /_\
  +-----------------------+\                              |                                                         
  | Strategy->algorithm() +-+    +------------------------+---------------------- ... 
  +-------------------------+    |                        |
                                 |                        |
                      +---------------------+  +----------------------+
                      | StrategyA           |  | StrategyB            |
                      +=====================+  +======================+
                      | algorithm()         |  | algorithm()          |
                      +---------------------+  +----------------------+

  Similarity to State Pattern - if you want to vary the algorithm or a behavior, 
  take the Strategy Pattern, if you want to vary the value, take the State Pattern.

  (GoF 1995)
//*/


#include <iostream>
#include <cmath>
#include <cstdlib>


/*
  Strategy
  
  - declares an interface common to all supported algorithms. Context 
  uses this interface to call the algorithm defined by a concrete 
  strategy.
//*/
class Strategy
{
public:
  virtual double algorithm(double arg) = 0;
};


/*
  StrategyA - a concrete strategy
  
  - implements the algorithm using the Strategy interface
//*/
class StrategyA
  : public Strategy
{
public:
  double algorithm(double arg)
  {
    std::cout << "\tStrategyA::algorithm()\n";
    return sin(arg);
  }
};


/*
  StrategyB - a concrete strategy
  
  - implements the algorithm using the Strategy interface
//*/
class StrategyB
  : public Strategy
{
public:
  double algorithm(double arg)
  {
    std::cout << "\tStrategyB::algorithm()\n";
    return cos(arg);
  }
};


/*
  Context
  
  - is configured with a concrete Strategy object
  - maintains a reference to a Strategy object
  - may define an interface that lets Strategy access its data
//*/
class Context
{
private:
  Strategy* pStrategy_;

public:
  Context(Strategy& strategy) : pStrategy_(&strategy)
  {
    std::cout << "\tContext::Context(Strategy&) - ctor\n";
  }

  double contextInterface(double arg)
  {
    std::cout << "\tContext::contextInterface(double) - context interface\n";
    arg = arg / 90 * 3.141592653589793238462643383;
    return pStrategy_->algorithm(arg);
  }
};


/*
  main
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  double angle = 90;
  cout << endl;

  cout << "first operation in sinus context\n";
  StrategyA sinus;
  Context sinusContext(sinus);
  cout << "sinus(" << angle << ") = " << sinusContext.contextInterface(angle) << " (= 0)\n";
  cout << endl;

  cout << "second operation in cosinus context\n";
  StrategyB cosinus;
  Context cosinusContext(cosinus);
  cout << "cosinus(" << angle << ") = " << cosinusContext.contextInterface(angle) << " (= -1)\n";
  cout << endl;

  cout << "READY.\n";
  return 0;
}

