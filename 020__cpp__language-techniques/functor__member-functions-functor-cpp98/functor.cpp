// functor.cpp
/*
  Parrot Geronimo

  Demo on memberfunctions - functor solution.

  (Alexandrescu, 2001)
//*/


#include <iostream>


#include "functor.hpp"


/*
  Parrot
//*/
class Parrot
{
public:
  void eat() { std::cout << "\tTsk, knick, tsk...\n"; }

  void speak() { std::cout << "\tOh Captain, my Captain!\n"; }
};


/*
template< class ParentFucntor, typename PointerToObj, typename PointerToMemFn >
class MemFunHandler
  : public FunctorImpl
{
public:
  typedef typename ParentFunctor::ResultType ResultType;
  MemFunHandler(const PoitnerToObj& pObj, PointerToMemFn pMemFn)
    : pObj_(pObj), pMemFn_(pMemFn)
  {}

  MemFunHandler* clone() const
  {
    return new MemFunHandler(*this);
  }

  ResultType operator()()
  {
    return ((*pObj_).*pMemFn_)();
  }

  ResultType operator()(typename ParentFunctor::Param1 p1)
  {
    return ((*pObj_).*pMemFn_)(p1);
  }

  ResultType operator()(typename ParentFunctor::Param1 p1, typename
ParentFunctor::Param2 p2)
  {
    return ((*pObj_).*pMemFn_)(p1, p2);
  }

private:
  PointerToObj pObj_;
  PointerToMemFn pMemFn_;
};
//*/


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  Parrot geronimo;
  cout << endl;


  // define two functors
  cout << "init two functors\n";
  Functor< void > cmd1(&geronimo, &Parrot::eat);
  Functor< void > cmd2(&geronimo, &Parrot::speak);
  cout << endl;


  // alternatively, Functor can have void as its default R parameter
  // invoke each of them
  cout << "invoke each of them\n";
  cmd1();
  cmd2();
  cout << endl;


  cout << "READY.\n";
  return 0;
}
