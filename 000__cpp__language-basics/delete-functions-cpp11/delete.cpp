/*
  C++11 - prefer delete functions to private undefined (Meyers / item 11)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - prefer deleted functions to private undefined ones

  - any function may be deleted, including non-member functions and template
    instantiations

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
//#include <traits>

using namespace std;

// C++98 approach
template <class charT, class traits = char_traits<charT> >
class Classic : public ios_base
{
public:
    // ...

private:
  // prohibited, but can still be used in 'friend' declared functions,
  // or implemented here
  Classic(const Classic&); // not defined
  Classic& operator=(const Classic&); // not defined
};


// C++11 approach
template <class charT, class traits = char_traits<charT> >
class Modern : public ios_base
{
public:
  // deleted functions are also prohibited for 'friend' functions
  Modern(const Modern& ) = delete;
  Modern& operator=(const Modern&) = delete;
};


class Box
{
public:
  bool isLucky(int number)
  {
    return true;
  }

  // and delete other variants, thus prohibit their implementation
  // and implicit conversions
  bool isLucky(char) = delete;
  bool isLucky(bool) = delete;
  bool isLucky(double) = delete;

  // when prohibiting e.g. 'char*' you need to prohibit 'void*', too
  void processPointer(char*) = delete;
  void processPointer(void*) = delete;

  // in case for template functions, syntax is as follows
  //template<>
  //void processPointer<void>(void*) = delete;
};

class DerrivedBox : public Box
{
public:
  // derrived classes MAY implement the prohibited functions, though
  void processPointer(char* arg){ cout << "CALLED: processPointer(char*)" << endl; }
};



int main(void)
{
  char* pch = nullptr;

  DerrivedBox db;
  db.processPointer(pch);

  cout << "READY." << endl;
}

