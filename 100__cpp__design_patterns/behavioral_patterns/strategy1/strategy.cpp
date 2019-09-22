// strategy.cpp
/*
  Define a family of algorithms, encapsulate each one, and make them
  interchangeble. Strategy lets the algorithm vary independently from clients
  that use it.

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


struct Strategy
{
  virtual ~Strategy(){}
  virtual double algorithm(double arg) = 0;
};


struct StrategyA : public Strategy
{
  double algorithm(double arg){ return sin(arg); }
};


struct StrategyB : public Strategy
{
  double algorithm(double arg){ return cos(arg); }
};


class Context
{
private:
  Strategy* pStrategy_;

public:
  Context(Strategy& strategy) : pStrategy_(&strategy)
  {}

  double contextInterface(double arg)
  {
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

  StrategyA sinus;
  Context sinusContext(sinus);
  cout << "sinus(" << angle << ") = " << sinusContext.contextInterface(angle) << " (= 0)\n";
  cout << endl;

  StrategyB cosinus;
  Context cosinusContext(cosinus);
  cout << "cosinus(" << angle << ") = " << cosinusContext.contextInterface(angle) << " (= -1)\n";
  cout << endl;

  cout << "READY.\n";
  return 0;
}

