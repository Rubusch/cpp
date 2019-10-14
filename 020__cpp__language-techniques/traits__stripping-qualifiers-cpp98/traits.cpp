// strippingtraits.cpp
/*
  "Traits are a generic programming technique that allows compile-time
  decisions to be made based on types, much as you would make runtime
  decisions based on values.

  This makes the resulting code cleaner, more readable, and easier to
  maintain."

  "Implementing a 'const stripper' is easy, again by using partial
  template specialization."

  This demonstrates the conversion of a 'const' declared TYPE. It has nothing
  directly to do with a const_cast!

  It serves to extract the non-'const' type of a constant type-DECLARATION
  (not constant or variable!!). These issue is a little tricky since it's not
  related directly to varables or instances.

  resources: Modern C++ Design, Alexandrescu
//*/


#include <iostream>


/*
  Type Traits
//*/
template < typename T >
class TypeTraits
{
private:
  // de-const Traits
  template < class U >
  struct UnConst {
    typedef U Result;
  };

  template < class U >
  struct UnConst< const U > {
    typedef U Result;
  };

public:
  // removes the 'const' qualifier from T, if any
  typedef typename UnConst< T >::Result NonConstType;
};


/*
  main
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  typedef const int MyType_t;

  MyType_t var1 = 123;
  cout << "var1 = " << var1 << "\n";
  cout << "re-init variable won't compile.\n";
  //  var1 = 777; // this won't compile!
  cout << endl;

  typedef TypeTraits< MyType_t >::NonConstType MyNewType_t;

  MyNewType_t var2 = 123;
  cout << "var2 = " << var2 << "\n";
  var2 = 777;
  cout << "re-init variable, var2 = " << var2 << "\n";
  cout << endl;


  cout << "READY.\n";
  return 0;
}
