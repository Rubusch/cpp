// strategy.cpp
/*
  Define a family of algorithms, encapsulate each one, and make them
interchangeble. Strategy lets the algorithm vary independently from clients that
use it.

  +---------------------+                     +-----------------------+
  | Context             |<>------------------>| Strategy              |
  +=====================+                     +=======================+
  |                     |                     |                       |
  +---------------------+                     +-----------------------+
  | contextInterface()  |                     | algorithm()           |
  +-|-------------------+                     +-----------------------+
    |                                                    /_\
  +-----------------------+\                              |
  | Strategy->algorithm() +-+ +------------------------+----------------------
...
  +-------------------------+    |                        |
                                 |                        |
                      +---------------------+  +----------------------+
                      | StrategyA           |  | StrategyB            |
                      +=====================+  +======================+
                      | algorithm()         |  | algorithm()          |
                      +---------------------+  +----------------------+

  Similarity to State Pattern - if you want to vary the algorithm or a behavior,
  take the Strategy Pattern, if you want to vary the value, take the State
Pattern.


  The current implementation avoids inheritance, and favors aggregation.
  Aggregation is better to maintain and leads to less complexity.



  RESOURCES

  * Design Patterns, GoF, 1995

  * Exceptional C++, Herb Sutter, 2000
//*/


#include <cmath>
#include <iomanip> /* setprecision() */
#include <iostream>
#include <memory>

/*
  Strategy

  - declares an interface common to all supported algorithms. Context
  uses this interface to call the algorithm defined by a concrete
  strategy.
//*/
struct Impl_Strategy {
  virtual ~Impl_Strategy() {}
  virtual double algorithm(double arg) = 0;
};

/*
  StrategyA - a concrete strategy

  - implements the algorithm using the Strategy interface
//*/
struct Impl_StrategyA : public Impl_Strategy {
  double algorithm(double arg)
  {
    std::cout << "\tImpl_StrategyA::algorithm()\n";
    return round(sin(arg));
  }
};


/*
  StrategyB - a concrete strategy

  - implements the algorithm using the Strategy interface
//*/
struct Impl_StrategyB : public Impl_Strategy {
  double algorithm(double arg)
  {
    std::cout << "\tImpl_StrategyB::algorithm()\n";
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
  double res_;

  void conversion()
  {
    std::cout << "\tContext::conversion()" << std::endl;
    res_ = res_ / 90 * 3.141592653589793238462643383;
  }

public:
  Context(std::shared_ptr< Impl_Strategy > pImpl, double arg) : res_(arg)
  {
    std::cout << "\tContext:CTOR()" << std::endl;
    conversion();
    res_ = pImpl->algorithm(res_);
  }

  const double &operator()() const { return res_; }
};


/*
  main
//*/
int main()
{
  using namespace std;

  cout << std::fixed << setprecision(3) << "init" << endl;
  double angle = 90;
  cout << endl;

  cout << "first operation in sinus context" << endl;
  auto sinus = Context(std::make_shared< Impl_StrategyA >(), angle);
  cout << "sinus(" << angle << ") = " << sinus() << " (= 0)" << endl;
  cout << endl;

  cout << "second operation in cosinus context" << endl;
  auto cosinus = Context(std::make_shared< Impl_StrategyB >(), angle);
  cout << "cosinus(" << angle << ") = " << cosinus() << " (= -1)" << endl;
  cout << endl;

  cout << "READY." << endl;
  return 0;
}
