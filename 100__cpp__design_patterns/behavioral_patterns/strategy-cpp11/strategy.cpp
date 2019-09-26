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
#include <memory>
#include <cmath>
#include <cstdlib>
#include <iomanip> /* setprecision() */

/*
  Strategy

  - declares an interface common to all supported algorithms. Context
  uses this interface to call the algorithm defined by a concrete
  strategy.
//*/
class Strategy
{
public:
  virtual ~Strategy(){}
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
    return round(sin(arg));
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
    return round(cos(arg));
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
  std::shared_ptr< Strategy > pStrategy_;

public:
//  Context(Strategy& strategy) // TODO rm
  Context(std::shared_ptr< Strategy > strategy)
    : pStrategy_( strategy )
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

  cout << "init" << endl;
  double angle = 90;
  cout << endl;

  cout << "first operation in sinus context" << endl;
  auto sinus = std::make_shared< StrategyA >();
  Context sinusContext(sinus);
  auto sin_res = sinusContext.contextInterface(angle);
  cout << std::fixed << setprecision(3) << "sinus(" << angle << ") = " << sin_res << " (= 0)" << endl;
  cout << endl;

  cout << "second operation in cosinus context" << endl;
  auto cosinus = std::make_shared< StrategyB >();
  Context cosinusContext(cosinus);
  auto cos_res = cosinusContext.contextInterface(angle);
  cout << "cosinus(" << angle << ") = " << cos_res << " (= -1)" << endl;
  cout << endl;

  cout << "READY." << endl;
  return 0;
}

