// bind.cpp
/*
  bind

  demostrates the usage of bind (C++11), argument reordering and pass-by-reference

  'std::bind' is likely to disappear in later versions of C++ than C++11



  placeholders

  _1, _2 and _3 are from std::placeholders, and represent future
  arguments that will be passed to a function when the function is called


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
  cout << n1 << '\t' << n2 << '\t' << n3 << '\t' << n4 << '\t' << n5 << '\n';
}


int anotherFunc(int n1)
{
  return n1;
}


struct SomeClass {
  int data = 10;

  void print_sum(int val1, int val2)
  {
    cout << val1 + val2 << '\n';
  }
};


int main()
{
  int num = 7;

  cout << "bind arguments to printer function, and create a parametrized printer object" << endl
       << "bind:\t\t[_2]\t42\t[_1]\t7\t7" << endl;
  auto printerObject = std::bind(printer, _2, 42, _1, std::cref(num), num);
  num = 10;
  // calling the printer object with arguments
  cout << "called:\t\t1\t2\t1001" << endl
       << "resulting:\t";
  printerObject(1, 2, 1001);
  cout << endl;
  // '1' is bound by '_1',
  // '2' is bound by '_2',
  // '1001' is unused
  // finally calls printerObject(2, 42, 1, n, 7)

  // nested bind subexpressions share the placeholders!!!
  cout << "nested bind in bind, the bind subexpression shares the placeholders!" << endl
       << "bind:\t\t[_3]\t[bind]\t4\t5\t// [_3] via nested bind() to anotherFunction" << endl;
  auto anotherPrinterObject = std::bind(printer, _3, std::bind(anotherFunc, _3), _3, 4, 5);
  cout << "called:\t\t10\t11\t12" << endl
       << "resulting:\t";
  // calls anotherPrinterObject(12, anotherFunc(12), 12, 4, 5);
  anotherPrinterObject(10, 11, 12);
  cout << endl;

  // create 10 values a uniform int distribution by a rng
  cout << "use case: bind a random number generator to a function object" << endl
       << "bind:\t\tuid\tdre" << endl;
  std::default_random_engine dre;
  std::uniform_int_distribution<> uid(0, 10);
  auto randomDistributionObject = std::bind(uid, dre); // a copy of dre is stored in rnd
  cout << "called:\t\t" << endl
       << "resulting:\t";
  for (auto cnt=0; cnt<10; ++cnt) {
    cout << randomDistributionObject() << '\t';
  }
  cout << endl << endl;

  // bind to a pointer to member function
  cout << "bind arguments to a member function pointer (summing up)" << endl
       << "bind\t\t&foo\t95\[_1]" << endl;
  SomeClass foo;
  auto memberFunctionObject = std::bind(&SomeClass::print_sum, &foo, 95, _1);
  cout << "called:\t\t5" << endl
       << "resulting:\t";
  memberFunctionObject(5);
  cout << endl;

  // bind to a pointer to data member
  cout << "bind a pointer to a data member as static instruction, then passing the specific object" << endl
       << "bind:\t\t" << "[_1]" << endl;
  auto dataMemberObject = std::bind(&SomeClass::data, _1);
  cout << "called:\t\tfoo" << endl
       << "resulting:\t";
  cout << dataMemberObject(foo) << endl;
  cout << endl;

  // smart pointers can be used to call members of the referenced objects, too
  cout << "now using smart pointers to the data member" << endl;
  cout << "shared ptr: " << dataMemberObject(make_shared<SomeClass>(foo)) << endl
       << "unique ptr: " << dataMemberObject(make_unique<SomeClass>(foo)) << endl;
  cout << endl;

  cout << "READY." << endl;
}
