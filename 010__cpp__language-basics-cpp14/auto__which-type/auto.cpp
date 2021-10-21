/*
  C++11 - How to figure out which type is used at 'auto'?

  ---
  approaches:
  - use IDE (hover over variable shows type)
  - go by the debugger and analyze
  - go by the compiler error message
  -- also: provoke a compiler error message

  an idea from Effective Modern C++ which uses non-implemented
  template; the type is output with compiler error:

    template<typename T> struct TD;

  Now for auto variable var, after its definition add:

    TD<decltype(var)> td;

  And watch error message for your compiler, it will contain type of
  var

  $ make clean && make
    rm -f auto.exe auto.o core *~
    g++  -g -Wall -Werror -std=c++11 -Wno-unused-variable  -c -o auto.o auto.cpp
    auto.cpp: In function ‘int main()’:
    auto.cpp:42:19: error: aggregate ‘TD<int> td’ has incomplete type and cannot be defined
       TD<decltype(x)> td;
                       ^~

  "aggregate ‘TD<int> td’" -> type deduces to "int"!!!

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <vector>

using namespace std;

template<typename T> struct TD; /* DECLARATION OF TOOL*/

int main(void)
{
  // adornments need still to be set
  auto x = 27; // deduces to 'int'
  cout << "auto x = 27;" << endl;
//  TD<decltype(x)> td; /* USAGE OF TOOL */

  const auto cx = x; // deduces to 'const int'
  cout << "const auto cx = x;" << endl;
//  TD<decltype(cx)> td; /* USAGE OF TOOL */

  const auto &rx = x; // deduces to 'const int&'
  cout << "const auto& rx = x;" << endl;
//  TD<decltype(rx)> td; /* USAGE OF TOOL */

  // problem: exact type unknown, auto identifies
  vector< int > vec;
  auto size = vec.size(); // deduces to 'unsigned int'
  cout << "vec.size() returned 'vector<int>::size_type' and not 'int' or "
          "'unsigned': "
       << endl;
  TD<decltype(size)> td; /* USAGE OF TOOL */

  cout << "READY." << endl;
}
