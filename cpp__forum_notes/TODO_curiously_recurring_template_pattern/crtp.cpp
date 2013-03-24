// crtp.cpp
/*
  curisously recurring template pattern

  www.c-plusplus.de/forum
//*/


#include <iostream>


// forward declaration
//template< class T > class Base;
//class Derived;


// base class
template< class T > 
class Base 
  : public T
{
public:
  Base()
  {
    std::cout << "\t\tBase< T >::Base() - ctor\n";
  }
};


class Dummy{};

// derived class
class Derived 
  : public Base< Dummy >//< Derived >
{
public:
  Derived()
  {
    std::cout << "\tDerived::Derived() - ctor\n";
  }
};


/*
  main...
//*/
int main()
{
  using namespace std;

  cout << "instantiate..";
  Derived d;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
