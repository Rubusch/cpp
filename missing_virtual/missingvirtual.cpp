// missingvirtual.cpp
/*
  Demonstrates the miss of a "virtual" declaration. The output will be "Base::play()" and not, 
  as expected to be, "Derived::play()", the new implementation will be hidden!

  But: multiple inheritance as also virtual functions (represented as vptrs in a vtbl per class)
  cost more memory and lower performance, due to they avoid inlining. (More Effective C++ / 23 / 
  Meyers)

  The solution is to prefer pure virtual functions and abstract classes!

  The RTTI information can be accessed via type_info and typeid
//*/

#include <iostream>


template<class T>
class Base
{
public:
  /*
    virtual - the as BASE passed object will call the function of the instance, hence of the derived 
    class!

    non-virtual - the as BASE passed object will call the (hidden) function of the base class, this 
    can be dangerous, since it's normally undesirable behaviour!!
  //*/

  //  virtual void play();      // virtual version
  void play();              // non-virtual version
};

template<class T>
void Base<T>::play()
{
  std::cout << "Base::play()" << std::endl;
}




template<class T>
class Derived : public Base<T>
{
public:
  void play();
};

template<class T>
void Derived<T>::play()
{
  std::cout << "Derived::play()" << std::endl;
}




template<class T>
void someFunction(Base<T>& obj)
{
  obj.play();
}





/*
  some main
//*/
int main()
{
  // instantiation of "Derived" obj
  Derived<std::string> d;

  // call and pass-by-reference - func takes anything derived from "Base"
  someFunction(d);

  std::cout << "READY.\n";
  return 0;
}
