// bind.cpp
/*
  bind

  demostrates the usage of bind (C++11), argument reordering and pass-by-reference

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

#include <iostream>
#include <random>
#include <memory>
#include <functional>

using namespace std;
using namespace std::placeholders;  // for _1, _2, _3...


void printer(int n1, int n2, int n3, const int& n4, int n5)
{
  cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}


int anotherFunc(int n1)
{
  return n1;
}


struct Foo {
  int data = 10;

  void print_sum(int val1, int val2)
  {
    cout << val1 + val2 << '\n';
  }
};


int main()
{
  int num = 7;

  // (_1 and _2 are from std::placeholders, and represent future
  // arguments that will be passed to func1)
  cout << "bind arguments to printer function" << endl;
  auto func1 = std::bind(printer, _2, 42, _1, std::cref(num), num);
  num = 10;
  func1(1, 2, 1001);
  cout << endl;
  // '1' is bound by '_1',
  // '2' is bound by '_2',
  // '1001' is unused
  //
  // this makes a call to func(2, 42, 1, n, 7)

  // nested bind subexpressions share the placeholders!!!
  cout << "nested bind subexpressions share the placeholders!" << endl;
  auto func2 = std::bind(printer, _3, std::bind(anotherFunc, _3), _3, 4, 5);
  func2(10, 11, 12); // makes a call to printer(12, anotherFunc(12), 12, 4, 5);
  cout << endl;

  // common use case: binding a RNG with a distribution
  std::default_random_engine dre;
  std::uniform_int_distribution<> uid(0, 10);
  auto rnd = std::bind(uid, dre); // a copy of e is stored in rnd
  for(int cnt=0; cnt<10; ++cnt) {
    cout << rnd() << ' ';
  }
  cout << endl;
 
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
