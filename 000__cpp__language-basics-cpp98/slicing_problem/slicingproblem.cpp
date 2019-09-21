//slicingproblem.cpp
/*
  assignment of a derrived class object into an object of its base class slices
  off the members of the derrived parts in the resulting object of class base
//*/

#include <iostream>
#include <string>

using namespace std;


class Base
{
protected:
  int temp;

public:
  Base(int initTemp);
  int getTemp();
};


Base::Base(int initTemp)
  :temp(initTemp)
{}

int Base::getTemp()
{
  return temp;
}


class Derived
: public Base
{
private:
  int newTemp;

public:
  Derived(int initNewTemp, int initTemp);
  int getNewTemp();
};

Derived::Derived(int initNewTemp, int initTemp)
  : Base(initTemp)
  , newTemp(initNewTemp)
{}

int Derived::getNewTemp()
{
  return newTemp;
}


/*
  some main
//*/
int main()
{
  int baseVar = 1, derivedBaseVar = 2, derivedVar = 22;

  Base base(baseVar);
  cout << "base:" << endl
       << "variable (base) = " << base.getTemp() << endl;

  Derived derived(derivedBaseVar, derivedVar);
  cout << "derived:" << endl
       << "variable (base) = " << derived.getTemp() << ";\t "
       << "variable (derived) = " << derived.getNewTemp() << endl;
  cout << endl;

  cout << "base = derived;" << endl;
/*
  Slicing Problem:
  slicing occurs here since the features of the derived class's
  object are not copied, though this kind of copy is allowed
*/
  base = derived;
  cout << "...after slicing the results are (base changed, but the Derived's attributes are \"sliced off\":" << endl << endl;

  cout << "base:" << endl
       << "variable (base) = " << base.getTemp() << endl;
  cout << "derived:" << endl
       << "variable (base) = " << derived.getTemp() << ";\t "
       << "variable (derived) = " << derived.getNewTemp() << endl;

  cout << "READY." << endl;
  return 0;
}
