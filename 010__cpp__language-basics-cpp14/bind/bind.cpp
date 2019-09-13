// bind.cpp
/*
  bind

  demostrates the usage of bind (C++11)

  'std::bind' is likely to disappear in later versions of C++ than C++11

  ---


  C++14 - prefer lambdas to std::bind
  (Meyers / item 34)


  CONCLUSION

  - Lambdas are more readable, more expressive, and may be more efficient than
    using 'std::bind'.

  - In C++11 only, 'std::bind' may be useful for implementing move capture or
    for binding objects with templatized function call operators.

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
//*/

#include <random>
#include <iostream>
#include <memory>
#include <functional>

using namespace std;
using namespace std::placeholders;  // for _1, _2, _3...


void func(int n1, int n2, int n3, const int& n4, int n5)
{
  cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}


int anotherFunc(int n1)
{
  return n1;
}


struct Foo {
  void print_sum(int n1, int n2)
  {
    cout << n1+n2 << '\n';
  }
  int data = 10;
};


int main()
{
  // demonstrates argument reordering and pass-by-reference
  int n = 7;
  // (_1 and _2 are from std::placeholders, and represent future
  // arguments that will be passed to func1)
  auto func1 = std::bind(func, _2, 42, _1, std::cref(n), n);
  n = 10;
  func1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
  // makes a call to func(2, 42, 1, n, 7)

  // nested bind subexpressions share the placeholders
  auto func2 = std::bind(func, _3, std::bind(anotherFunc, _3), _3, 4, 5);
  func2(10, 11, 12); // makes a call to func(12, anotherFunc(12), 12, 4, 5);

  // common use case: binding a RNG with a distribution
  std::default_random_engine e;
  std::uniform_int_distribution<> d(0, 10);
  auto rnd = std::bind(d, e); // a copy of e is stored in rnd
  for(int n=0; n<10; ++n) {
    cout << rnd() << ' ';
  }
  cout << '\n';

  // bind to a pointer to member function
  Foo foo;
  auto func3 = std::bind(&Foo::print_sum, &foo, 95, _1);
  func3(5);

  // bind to a pointer to data member
  auto func4 = std::bind(&Foo::data, _1);
  cout << func4(foo) << '\n';

  // smart pointers can be used to call members of the referenced objects, too
  cout << func4(std::make_shared<Foo>(foo)) << '\n'
       << func4(std::make_unique<Foo>(foo)) << '\n';
}
