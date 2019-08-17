/*
  C++11 - prefer auto to explicit type declarations (Meyers / item 7)

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

using namespace std;

class Widget{};

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
  cout << "most vexing parse, init: e{} and declaration f()" << endl;
  Widget e{}; // calls constructor with no arguments
  Widget f(); // THIS is a function declaration, not a variable definition!!!
  cout << endl;

  // vector special situation with braces and parens
  cout << "special constructor calls: vector<int>" << endl;
  vector<int> vec1{ 10, 20 };
  cout << "vec1{ 10, 20 } - vec1.size(): " << vec1.size() << endl;

  vector<int> vec2( 10, 20 );
  cout << "vec2( 10, 20 ) - vec2.size(): " << vec2.size() << endl;

  cout << endl;


  // where it must be braces
  

  cout << "READY." << endl;
}

