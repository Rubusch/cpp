// ambiguous.cpp
/*
  ambiguous naming is possible due to different parameters, a different return
  value leads to a compile error!


  Generally try to avoid inheritance in favor of aggregation patterns.
  Inheritance is only needed when virtual functions (functions need to be
  overwriteable), or members are within a protected block are around.
  By Liskov public inheritance implements a 'IS-A' relation. Everything else
  should be modeled as aggregation 'HAS-A', or 'IS-IMPLEMENTED-WITH' (which
  can also be private inheritance). [Sutter, 2000]


  RESOURCES

  * Scott Meyers, lection 26

  * Exceptional C++, Herb Sutter, 2000
//*/

#include <iostream>

using namespace std;


class Base1
{
public:
  virtual ~Base1(){}
  void ambiguous_param(char chr){ cout << "Base1 - param: " << chr << endl; }
  int ambiguous_return(){ return 7; }
};

void global_ambiguous_param(char chr){ cout << "global - param: " << chr << endl; }
//int global_ambiguous_return(){ return 7; }


class Base2
{
public:
  virtual ~Base2(){}
  void ambiguous_param(int i){ cout << "Base1 - param: " << i << endl; }
  char ambiguous_return(){ return 'd'; }
};

void global_ambiguous_param(int i){ cout << "global - param: " << i << endl; }
//char global_ambiguous_return(){ return 'd'; }


class Derived: public Base1, public Base2
{
public:
  void doSomething(){ cout << "Derived - works fine!" << endl; }
  // do something, but don't reimplement the functions (not virtual!)
};


/*
  call to main
//*/
int main()
{
  Derived d;
  d.doSomething();

  // some param
  char chr = 'c';

  //*// global functions with ambigous names
  global_ambiguous_param(static_cast<int>(chr));
  global_ambiguous_param(static_cast<char>(chr));
  //*/

  /*// ambiguous names with different return value type in global functions
    // fails, due to "re-declaration of function"!
  chr = global_ambiguous_return();
  cout << "Derived - chr: " << chr << endl;
  //*/

  /*// ambiguous params in a class inheritance - fails!
  d.ambiguous_param(static_cast<int>(chr));
  d.ambiguous_param(static_cast<char>(chr));
  //*/

  /*// ambiguous return value - fails!
  chr = static_cast<char>(d.ambiguous_return());
  cout << "Derived - chr: " << chr << endl;
  //*/
  return 0;
}
