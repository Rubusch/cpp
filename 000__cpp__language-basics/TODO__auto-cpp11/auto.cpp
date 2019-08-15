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
void isConst(const int& arg) { cout << "const int&"; }
void isConst(int& arg) { cout << "int&"; }
void isConst(const int* arg) { cout << "const int*"; }
void isConst(int* arg) { cout << "int*"; }
void isConst(int&& arg) { cout << "int&&"; }



int main(void)
{
// adornments need still to be set
  auto x = 27;
  const auto cx = x;
  const auto& rx = x;

  cout << "x: ";
  isConst(x);
  cout << endl;

  cout << "cx: ";
  isConst(cx);
  cout << endl;

  cout << "rx: ";
  isConst(rx);
  cout << endl;


  // TODO

  cout << "READY." << endl;
}

