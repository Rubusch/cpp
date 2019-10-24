// functorhandler.cpp
/*
  Demonstrates the usage of a more sophisticated functor implementation.
  1. usage of the functor with a functor class
  2. usage of the functor with a functor function
  3. usage of the binding mechanism, binding a given parameter to another
  and the call of a command (functor)

  (Alexandrescu, 2001)

  roughly updated for cpp11
//*/


#include <iostream>

#include "functor.hpp"

using namespace std;


/*
  functor class

  test class for the functor
//*/
struct TestClassFunctor {
  void operator()(int i, double d)
  {
    cout << "TestClassFunctor::operator()(" << i << ", " << d << ") called.\n";
  }
};


/*
  functor function

  test functor command as function
//*/
void testFunctionFunctor(int i, double d)
{
  cout << "testFunctionFunctor(" << i << ", " << d << ") called.\n";
}


int main()
{
  // 1. test class
  cout << "1. Functor Class\n";
  TestClassFunctor func;
  Functor< void, TL::Typelist< int, double > > cmd_1(func);
  cmd_1(1, 2.3);
  cout << endl;


  // 2. test function
  // pass function implicit function pointer to the functor implementation
  cout << "2. Functor Function\n";
  Functor< void, TL::Typelist< int, double > > cmd_2(testFunctionFunctor);
  cmd_2(1, 2.3);
  cout << endl;


  // 3. overloaded function functor
  // typedef used for convenience
  cout << "3. Overloaded Function Functor\n";
  using pFun_t = void (*)(int, double);

  // method 1: use an initialization
  cout << "3.a Method: initialized function pointer\n";
  pFun_t pF = testFunctionFunctor;
  Functor< void, TL::Typelist< int, double > > cmd_3a(pF);
  cmd_3a(1, 2.3);

  // method 2: use a cast
  cout << "3.b Method: constructor call and static_cast<>()\n";
  Functor< void, TL::Typelist< int, double > > cmd_3b(
      static_cast< pFun_t >(testFunctionFunctor));
  cmd_3b(1, 2.3);
  cout << endl;


  cout << "READY.\n";
  return 0;
}
