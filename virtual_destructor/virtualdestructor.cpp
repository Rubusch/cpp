// virtualdestructor.cpp
/*
  demonstrate the usage of a virtual destructor

  Make a destructor virtual if a base class contains virtual functions! 

  Virtual function need to have a default implementation or result in a Linker Error!
  Alternatively make the function declarations "pure virtual" using:
  =0
  Then the default implementation is optional.
//*/


#include <iostream>

template< class T > class Base;
template< class T > class Derived;



/*
  base class
//*/
template< class T >
class Base
{
protected:
  T value;

public:
  Base();
  virtual ~Base() = 0; // makes the class abstract!
  
  /*
    F U N C T I O N S

    virtual functions 

    - virtual functions need a default implementation or will lead to a linker error!
    - only pure virtual function (= 0) won't lead to a linker error without implementation.
  //*/

  virtual void setValue(T val);
  virtual T getValue() = 0; // should be defined "= 0" or should contain code to return something 
};

template< class T >
Base< T >::Base()
{}

template< class T >
Base< T >::~Base()
{}

template< class T >
void Base< T >::setValue(T val)
{}

template< class T >
T Base< T >::getValue()
{}



/*
  some derived class
//*/
template< class T > 
class Derived : public Base< T >
{
public:
  Derived();
  ~Derived();

  void setValue(T val);
  T getValue();
};

template< class T >
Derived< T >::Derived()
{}

template< class T >
Derived< T >::~Derived()
{}

template< class T >
void Derived< T >::setValue(T val)
{
  Base< T >::value = val;
}

template< class T >
T Derived< T >::getValue()
{
  return Base< T >::value;
}



/*
  some main()
//*/
int main()
{
  // init
  Derived< int > d;

  // intput
  std::cout << "set a value" << std::endl;
  d.setValue(123);

  // output
  std::cout << "the value was: " << d.getValue() << std::endl;


  std::cout << "READY.\n" << std::endl;
  return 0;
}
