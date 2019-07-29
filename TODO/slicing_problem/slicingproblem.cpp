//slicingproblem.cpp
/*
  assignment of a derrived class object into an object of its base class slices
  off the members of the derrived parts in the resulting object of class base
//*/

#include <iostream>
#include <string>

using namespace std;


/*
  some base class
//*/
template<class T>
class Base
{
protected:
  T temp;

public:
  Base(T initTemp);
  T getTemp();
};

template<class T>
Base<T>::Base(T initTemp)
  :temp(initTemp)
{}

template<class T>
T Base<T>::getTemp()
{
  return temp;
}


/*
  some derived class
//*/
template<class T>
class Derived
: public Base<T>
{
private:
  T newTemp;

public:
  Derived(T initNewTemp, T initTemp);
  T getNewTemp();
};

template<class T>
Derived<T>::Derived(T initNewTemp, T initTemp)
  : Base<T>(initTemp)
    , newTemp(initNewTemp)
{}

template<class T>
T Derived<T>::getNewTemp()
{
  return newTemp;
}


/*
  some main
//*/
int main()
{
  int baseVar = 1, derivedBaseVar = 2, derivedVar = 22;

  Base<int> base(baseVar);
  cout << "base:\nvariable (base) = " << base.getTemp() << endl;

  Derived<int> derived(derivedBaseVar, derivedVar);
  cout << "derived:\nvariable (base) = " << derived.getTemp() << ";\t variable (derived) = " << derived.getNewTemp() << endl;

  cout << endl;

  cout << "base = derived;" << endl;
/*
  Slicing Problem:
  slicing occurs here since the features of the derived class's
  object are not copied, though this kind of copy is allowed
*/
  base = derived;
  cout << "...after slicing the results are (base changed, but the Derived's attributes are \"sliced off\":" << endl << endl;

  cout << "base:\nvariable (base) = " << base.getTemp() << endl;
  cout << "derived:\nvariable (base) = " << derived.getTemp() << ";\t variable (derived) = " << derived.getNewTemp() << endl;

  cout << "READY.\n";
  return 0;
}
