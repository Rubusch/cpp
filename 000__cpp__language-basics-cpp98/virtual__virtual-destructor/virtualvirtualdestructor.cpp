// virtualdestructor.cpp
/*
  demonstrate the usage of a virtual destructor



  PROVIDE A VIRTUAL DESTRUCTOR IF A BASE CLASS CONTAINS VIRTUAL FUNCTIONS!!!



  If a virtual destructor is missing, destruction of a dynamically allocated
  derrived class object won't call the correct base class destructor, memory
  and/or resource leaks are the consequence. Probably compilers won't complain
  about.

  Virtual function need to have a default implementation or result in a Linker Error!
  Alternatively make the function declarations "pure virtual" using:
  =0
  Then the default implementation is optional.

  A destructor should never throw any exception, it should absorb them and/or
  not forward them.

  ---

  Generally try to avoid inheritance in favor of aggregation patterns.
  Inheritance is only needed when virtual functions (functions need to be
  overwriteable), or members are within a protected block are around.
  By Liskov public inheritance implements a 'IS-A' relation. Everything else
  should be modeled as aggregation 'HAS-A', or 'IS-IMPLEMENTED-WITH' (which
  can also be private inheritance). [Sutter, 2000]


  RESOURCES

  * Exceptional C++, Herb Sutter, 2000
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
