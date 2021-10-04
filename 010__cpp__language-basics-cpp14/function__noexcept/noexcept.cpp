/*
  C++11 - declare functions noexcept if they won't emit exceptions
  (Meyers / item 14)

  ---

  lvalue - has an address, e.g. a user maintained variable or memory
           with accessible address

  rvalue - has no accessible address, e.g. a plain number value
           (stored only temporarlily)


  conclusion:

  - noexcept is part of a function's interface, and that means that
    callers may depend on it

  - noexcept functions are more optimizable than non-except functions

  - noexcept is particularly valuable for the move operations, swap,
    memory deallocation functions and destructors

  - most functions are exception-neutral rather than noexcept

  - if noexcept is missing, default is noexcept(false), only exception
    are constructors and destructors which are noexcept(true)

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <exception>
#include <iostream>

using namespace std;


// noexcept: function context
void setup() { cout << "setup()" << endl; }

void cleanup() { cout << "cleanup()" << endl; }

/*
int func(int x) throw(); // no exceptions from func(), C++98 style
{
  cout << "func()" << endl;
  setup();
  cleanup();
  return 0;
}
/*/
int func(int x) noexcept // no exceptions from func(), C++11 style
{
  cout << "func()" << endl;
  setup();
  cleanup();
  return 0;
}
// */


// C++14 example 'noexcept'
class HorrorException : public exception
{
public:
  virtual const char *what() const throw()
  {
    return "HORROR EXCEPTION RAISED!";
  }
};

HorrorException HEX;

class Box
{
public:
  void throwing_function() noexcept(false)
  {
    cout << "CALLED: Box::throwing_function()" << endl;
    if (some < 700) {
      throw HEX;
    }
  }

  void exceptionless_function() noexcept
  {
    cout << "CALLED: Box::exceptionless_function()" << endl;
  }

  void unspecified_function()
  {
    cout << "CALLED: Box::unspecified_function()" << endl;
  }

private:
  int some{123};
};


int main(void)
{
  cout << "noexcept: basic" << endl;
  func(7);
  cout << endl;


  cout << "noexcept in class context: via static_assert" << endl;
  Box box;

  try {
    box.exceptionless_function();
    box.unspecified_function();
    box.throwing_function();
  } catch (HorrorException &he) {
    cout << "=> caught exception: " << he.what() << endl;
  }
  cout << endl;

  cout << "READY." << endl;
}
