// abstractclass.cpp
/*
  to make a class abstract it is sufficient to declare the destructor completely
  "virtual"

  the example uses a template implementation to demonstrate
//*/


#include <iostream>


/*
  a completely abstract class
//*/
template<class T>
class AbstractBase
{
private:
  T exampleVariable;

public:
  // ...
  AbstractBase();
  virtual ~AbstractBase() = 0;
};

// a constructor for the abs class
template<class T>
AbstractBase<T>::AbstractBase()
{
  std::cout << "AbstractBase Ctor" << std::endl;
}

// this line is necessary!
template<class T>
AbstractBase<T>::~AbstractBase(){}



/*
  some derived class
//*/
template<class T>
class Derived
  : public AbstractBase<T>
{
public:
  Derived();
};

template<class T>
Derived<T>::Derived()
{
  std::cout << "Dervied Ctor" << std::endl;
}



/*
  use the classes in main()
//*/
int main()
{
  Derived<int> d;

  std::cout << "READY.\n" << std::endl;
  return 0;
}
