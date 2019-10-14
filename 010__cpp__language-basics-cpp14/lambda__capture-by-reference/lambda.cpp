// lambda.cpp
/*
  Lambda (>=cpp11) constructs a closure: an unnamed function object capable of
capturing variables in scope.

  This example shows dangers at capture by-reference.


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
      mutable = allows the body to modify copied params and to call their
non-const member functions exception = exception specification, or noexcept
      attribute = attribute specificatio for the closure type

    return type or use auto for closure, defaults to "void" (opt)

  {return x * y > 123; }; : function body
    implementation of the lambda class



  C++11 - avoid default capture modes
  (Meyers / item 31)

  C++11 - use init capture to move objects into closures
  (Meyers / item 32)

  CONCLUSION

  - Default by-reference capture can lead to dangling references.

  - Default by-value capture is susceptible to dangling pointers (especially
this), and it misleadingly suggests that lambdas are self-contained.

  - User C++14's init capture to move objects into closures.

  - In C++11, emulate init capture via hand-written classes or std::bind

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
//*/

#include <functional>
#include <iostream>
#include <vector>

using namespace std;


// function pointer type for container and container definition
using FilterContainer = std::vector< std::function< bool(int) > >;

// container instance
FilterContainer filters;

void addFilter_byReferenceDangling()
{
  auto divisor = 2;

  // fails, and only returns '0', since by-reference will dangle the reference
  // to function local 'divisor' when executed via the container somewhere else
  // [&] - if 'divisor' would be defined here, the by-reference capture would
  //       dangle since 'divisor's scope is function local to this add function!
  filters.emplace_back([&](int value) { return value % divisor == 0; }
                       // DANGER: reference to 'divisor' will dangle!!!
  );
}


void addFilter_byReferenceAlsoDangling()
{
  auto divisor = 2;

  // C++14 allows auto parameters, still same problem: dangling reference to
  // 'divisor' as above
  filters.emplace_back([&](const auto &value) { return value % divisor == 0; }
                       // DANGER: reference to 'divisor' will dangle!!!
  );
}

void addFilter_byValue()
{
  auto divisor = 2;
  // [=] - the solution: by-value capture
  filters.emplace_back([=](int value) { return value % divisor == 0; });
}

void addFilter_byValueStatic()
{
  static auto divisor =
      2; // should be static, since the closure are not self-contained
  // to make them more "self contained" passed values should be static
  // [] - fails, no local variable
  // [divisor] - fails, also since no local variable can be passed
  filters.emplace_back([=](int value) { return value % divisor == 0; });
}

/*
void addFilter_byReferenceInitCaptureCpp11()
{
  auto divisor = 2;

  // init capture - moved local variable into the closure

  // 1. moving the object to be captured into a function object produced by
std::bind and
  // 2. giving the lambda a reference to the captured object
  //
  // this technique does not allow easily mixing init captured params with
regular params (set later)
  //
  filters.emplace_back(
      std::bind( [](int value, const int& divisor) mutable { return value %
divisor == 0; }, TODO: expression for 'value' may be caputred later,
std::move(divisor) )
                       );
}
// */

void addFilter_byReferenceInitCaptureCpp14()
{
  auto divisor = 2;

  // init capture - moved local variable into the closure
  filters.emplace_back([divisor = std::move(divisor)](int value) {
    return value % divisor == 0;
  });
}


int main(void)
{
  addFilter_byReferenceDangling(); // not working due to dangling reference,
                                   // always returning '0', though no warning /
                                   // error
  addFilter_byReferenceAlsoDangling(); // not working due to dangling reference,
                                       // always returning '0', though no
                                       // warning / error
  addFilter_byValue();
  addFilter_byValueStatic();
  //  addFilter_byReferenceInitCaptureCpp11();
  addFilter_byReferenceInitCaptureCpp14();

  for (int idx = 0; idx < 3; ++idx) {
    for (const auto &filtered : filters) {
      // print the lambda computed value and verify
      cout << "item(" << idx
           << ") : " << (filtered(idx) == (idx % 2 == 0) ? "ok" : "failed")
           << endl;
    }
    cout << endl;
  }

  cout << "READY." << endl;
}
