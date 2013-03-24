//slicingproblem.cpp
/*

//*/

#include <iostream>
#include <string>


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
class Derived : public Base<T>
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
  std::cout << "base:\nvariable (base) = " << base.getTemp() << std::endl;
  
  Derived<int> derived(derivedBaseVar, derivedVar);
  std::cout << "derived:\nvariable (base) = " << derived.getTemp() << ";\t variable (derived) = " << derived.getNewTemp() << std::endl;

  std::cout << std::endl;

  // slicing Problem: slicing occurs here since the features of the derived class's object are not copied, though this kind of copy is allowed
  base = derived;

  std::cout << "...after slicing the results are (base changed, but the Derived's attributes are \"sliced off\":" << std::endl;
  std::cout << "base:\nvariable (base) = " << base.getTemp() << std::endl;
  std::cout << "derived:\nvariable (base) = " << derived.getTemp() << ";\t variable (derived) = " << derived.getNewTemp() << std::endl;

  std::cout << "READY.\n";
  return 0;
}
