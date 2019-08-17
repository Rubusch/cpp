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


int main(void)
{
  using UPtrMapSS = std::unique_ptr< std::unordered_map< std::string, std::string> >;


/*
  typedef void (*FP)(int, const std::string&);
/*/
  using FP = void (*)(int, const std::string&);
// */

//  remove_const
  
// TODO
  

  cout << "READY." << endl;
}

