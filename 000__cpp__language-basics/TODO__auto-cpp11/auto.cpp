/*
  C++11 - prefer auto to explicit type declarations (Meyers / item 5)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - auto variables must be initialized, are generally immune to type mismatches
    that can lead to portability or efficiency problems, can ease the process of
    refactoring, and typically require less typing than variables with
    explicitly specified types.

  - auto-typed variables are subject to the pitfalls such as proxy classes (with
    invisible types) and auto type deductions (as undesired fallback)

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


// type investigation via polymorphic
void isConst(const int& arg) { cout << " -> const int" << endl; }
void isConst(int& arg) { cout << " -> int" << endl; }



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

  const auto& rx = x;
  cout << "const auto& rx = x;" << endl;
  isConst(rx);
  cout << endl;

  // problem1: undesired fallbacks

  // problem2: proxy classes with hidden types
  // TODO

  cout << "READY." << endl;
}

