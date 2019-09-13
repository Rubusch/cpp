// lambda.cpp
/*
  Lambda (>=cpp11) constructs a closure: an unnamed function object capable of capturing variables in scope.

  This example shows to use 'decltype' on 'auto&&' paramters for 'std::forward'.


  ---


  fundamentals
  ------------

  int x = 10;
  (...)
  auto var = [x] (int y) constexpr -> int {return x * y > 123; };



  syntax variants:

  [capture] (params) mutable exception attribute -> ret { body }
  [capture] (params) -> ret { body }
  [capture] (params) { body }
  [capture] { body }



  terminology:

  auto var : closure
    the lambda object is called 'closure'

  [x] : capture
    which symbols are captured and thus visible for the lambda body, e.g.
    [a,&b]   a as by value copy, b as reference
    [this]   this pointer as a by value copy
    [&]      by-reference: all symbols available in function scope as reference
    [=]      by-value: all symbols available in function scope as a copy
    []       nothing captured
    CAUTION: references can be dangling references!

  (int y) : params
    list of parameters

  constexpr -> int : (optional, can be left out)
    specifier: mutable, constexpr, consteval (opt)
    where:
      mutable = allows the body to modify copied params and to call their non-const member functions
      exception = exception specification, or noexcept
      attribute = attribute specificatio for the closure type

    return type or use auto for closure, defaults to "void" (opt)

  {return x * y > 123; }; : function body
    implementation of the lambda class



  C++11 - use 'decltype' on 'auto&&' parameters to 'std::forward' them
  (Meyers / item 33)

  CONCLUSION

  - Use 'decltype' on 'auto&&' parameters to 'std::forward' them.

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
//*/

#include <iostream>

using namespace std;

// lambda to filter by '%3'
//*
auto closure = [](auto par){ return (par % 3); };
/*/ // generates something like this
class CompilerGeneratedClosureClassName
{
public:
  template< typename T >
  auto operator()(T par) const
  { return (par % 3); }
};
auto closure = CompilerGeneratedClosureClassName();
// */

// if lambda treats lvalues differently from rvalues, the above lambda is not sufficient (perfect forwarding)
auto forwardingClosure = [](auto&& par){ return std::forward< decltype(par) >(par) %3; };

// variadic extension of the lambda
// FIXME
//auto variadicClosure = [](auto&& ...par){ return (std::forward< decltype(par) >(par)...) %3; };


int main(void)
{
  for (auto idx=0; idx<10; ++idx) {

    cout << "item(" << idx << ") : " << closure(idx)
         << ", forwarding closure: " << forwardingClosure(idx)
//         << ", variadic: " << variadicClosure(idx)
         << endl;
  }
  cout << "READY." << endl;
}
