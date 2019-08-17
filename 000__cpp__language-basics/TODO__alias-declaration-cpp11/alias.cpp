/*
  C++11 - prefer alias declarations to typedef (Meyers / item 9)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - typedefs don't support templatization, but alias declaration (using) do

  - alias templates avoid the "::type" suffix and, in templates the "typename"
    prefix often required to refer to typedefs

  - C++14 offers alias templates for all the C++11 type traits transformations

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;


// templated aliases must be here, outside block scope!
// use _'_t' for the alias name
template <class T>
using remove_const_t = typename remove_const<T>::type;

template <class T>
using remove_reference_t = typename remove_reference<T>::type;

template <class T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;



int main(void)
{

  // using declaration (alias)
  using UPtrMapSS = std::unique_ptr< std::unordered_map< std::string, std::string> >;


  // instead of typedef, use "using" declaration
/*
  typedef void (*FP)(int, const std::string&);
/*/
  using FP = void (*)(int, const std::string&);
// */


  // using declaration even can handle templates, e.g. remove_const
  cout << "std::remove_const<T>::type -> std::remove_const_t<T>" << endl;
  // see above alias definitions

  cout << "READY." << endl;
}
