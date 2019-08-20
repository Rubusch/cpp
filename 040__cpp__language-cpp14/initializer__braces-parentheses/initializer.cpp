/*
  C++11 - distinguish between () and {} (Meyers / item 7)

  ---

  braces           {}

  parenthesis      ()

  square brackets  []

  angular brackets <>


  conclusion:

  - braced initalization is the most widely usable initialization syntax, it
    prevents narrowing conversions, and it's immune to C++'s most vexing parse

  - during constructor overload resolution, braced initializers are matched to
    std::initializer_list parameters if at all possible, even if other
    constructors offer seeemingly better matches

  - an example of where the choice between parentheses () and braces {} can make
    a significant difference is creating a std::vector<numeric type> with two
    arguments

  - choosing between parenthesis and braces for object creation inside templates
    can be challenging

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <vector>
#include <atomic>

using namespace std;


class WidgetA
{
  private:
  int x{ 0 };
  int y = 0;
//  int z(0); // ERROR! most-vexing-parse situation, must be braces
};

class WidgetB
{
  public:
    WidgetB() { cout << "CALLED: WidgetB()" << endl; }
    WidgetB(int i, bool b) { cout << "CALLED: WidgetB(int, bool)" << endl; }
    WidgetB(int i, double d) { cout << "CALLED: WidgetB(int, double)" << endl; }
};

class WidgetC
{
  public:
    WidgetC() { cout << "CALLED: WidgetC()" << endl; }
    WidgetC(int i, bool b) { cout << "CALLED: WidgetC(int, bool)" << endl; }
    WidgetC(int i, double d) { cout << "CALLED: WidgetC(int, double)" << endl; }
    WidgetC(std::initializer_list<long double> il) { cout << "CALLED: WidgetC(initializer_list<long double>)" << endl; }
};

int main(void)
{
  // initialization methods
  cout << "initialization:" << endl;
  int a(0);
  cout << "int a(0); a == " << a << endl;

  int b = 0;
  cout << "int b = 0; b == " << b << endl;

  int c{ 0 };
  cout << "int c{ 0 }; c == " << c << endl;
  cout << endl;

  // also combinations are possible
  cout << "combined initialization methods:" << endl;
  int d = { 0 };
  cout << "int d = { 0 }; d == " << d << endl;
  cout << endl;

  // most vexing parse
  cout << "most vexing parse, initialization" << endl;
  cout << "WidgetA e{}; - calls constructor with empty arguments" << endl;
  WidgetA e{};
  cout << "WidgetA f(); - a function declaration!!!" << endl;
  WidgetA f(); // THIS is a function declaration, not a variable definition!!!
  cout << endl;


  // where it must be braces: uncopyable objects, e.g. atomic, must be initialized using braces
  cout << "initialization of noncopyable objects" << endl;
  std::atomic<int> ai1{ 0 };
  std::atomic<int> ai2( 0 );
//  std::atomic<int> ai3 = 0; // ERROR!
  cout << endl;

  // ATTENTION: initializer_list catches all
  cout << "initializing an object" << endl;
  cout << "WidgetB w1(10, true); ";
  WidgetB w1(10, true);
  cout << "WidgetB w2{10, true); ";
  WidgetB w2{10, true};
  cout << "WidgetB w3(10, 7.9); ";
  WidgetB w3(10, 7.9);
  cout << "WidgetB w4{10, 7.9}; ";
  WidgetB w4{10, 7.9};
  cout << endl;

  cout << "now using initializer_list (is hijacking other constructor signatures)" << endl;
  cout << "WidgetC w5(10, true); ";
  WidgetC w5(10, true);
  cout << "WidgetC w6{10, true); ";
  WidgetC w6{10, true};
  cout << "WidgetC w7(10, 7.9); ";
  WidgetC w7(10, 7.9);
  cout << "WidgetC w8{10, 7.9}; ";
  WidgetC w8{10, 7.9};
  cout << endl;

  // vector special situation with braces and parens
  cout << "example: vector<int> using initializer lists" << endl;
  vector<int> vec1{ 10, 20 };
  cout << "vec1{ 10, 20 } - vec1.size(): " << vec1.size() << endl;

  vector<int> vec2( 10, 20 );
  cout << "vec2( 10, 20 ) - vec2.size(): " << vec2.size() << endl;
  cout << endl;

  cout << "READY." << endl;
}

