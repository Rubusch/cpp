/*
  C++11 - prefer auto to explicit type declarations (Meyers / item 5)

  ---

  lvalue - has an address, e.g. a user maintained variable or memory
           with accessible address

  rvalue - has no accessible address, e.g. a plain number value
           (stored only temporarlily)


  conclusion:

  - auto variables must be initialized, are generally immune to type
    mismatches that can lead to portability or efficiency problems,
    can ease the process of refactoring, and typically require less
    typing than variables with explicitly specified types.

  - auto-typed variables are subject to the pitfalls such as proxy
    classes (with invisible types) and auto type deductions (as
    undesired fallback)

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <vector>

using namespace std;


// type investigation via polymorphic
void isConst(const int &arg) { cout << " -> const int" << endl; }
void isConst(int &arg) { cout << " -> int" << endl; }
void isConst(unsigned &arg) { cout << " -> unsigned" << endl; }
void isConst(vector< int >::size_type &arg)
{
  cout << " -> vector<int>::size_type" << endl;
}


int main(void)
{
  // adornments need still to be set
  auto x = 27;
  cout << "auto x = 27;" << endl;
  isConst(x);
  cout << endl;

  const auto cx = x;
  cout << "const auto cx = x;" << endl;
  isConst(cx);
  cout << endl;

  const auto &rx = x;
  cout << "const auto& rx = x;" << endl;
  isConst(rx);
  cout << endl;

  // problem: exact type unknown, auto identifies
  vector< int > vec;
  auto size = vec.size();
  cout << "vec.size() returned 'vector<int>::size_type' and not 'int' or "
          "'unsigned': "
       << endl;
  isConst(size);

  cout << "READY." << endl;
}
