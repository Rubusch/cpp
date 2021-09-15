/*
  C++11 - prefer auto to explicit type declarations (Meyers / item 6)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - invisible proxy types can cause auto to deduce the wrong type for
    an initializing expression

  - the explicitly typed initializer idiom forces auto to deduce the
    type you want it to have

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <vector>

using namespace std;


// type investigation via polymorphic
void isConst(const int &arg) { cout << " -> const int" << endl; }
void isConst(int &arg) { cout << " -> int" << endl; }
void isConst(bool &arg) { cout << " -> bool" << endl; }


vector< bool > features() { return vector< bool >(20, true); }

int main(void)
{
  // problem: hidden types, now auto can't identify correctly
  //
  // example:
  // indexed access of a vector<bool>, i.e. a vector templated with
  // 'bool' does not allow 'auto' to identify its template type in
  // C++11, it falls back to 'const int' - operator[]() for vector
  // hides vectors template type, it is similar to a proxy pattern
  vector< bool > vec(10, true);
  auto prio = vec[7];
  cout << "vector<bool> vec(10, true);" << endl;
  isConst(prio);
  cout << " WRONG! should be 'bool'" << endl;
  cout << endl;

  auto returned_prio = features()[7];
  cout << "auto returned_prio = features(wg)[7];" << endl;
  isConst(returned_prio);
  cout << " WRONG! should be 'bool'" << endl;
  cout << endl;

  // solution:
  // use the explicitely typed initializer pattern (Meyers)
  // i.e. static_cast<>() together with auto
  auto correct_prio = static_cast< bool >(features()[7]);
  cout << "auto correct_prio = static_cast<bool>( features()[7] );" << endl;
  isConst(correct_prio);
  cout << endl;


  cout << "READY." << endl;
}
