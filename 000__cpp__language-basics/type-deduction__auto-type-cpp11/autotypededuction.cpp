/*
  C++11 - auto type deduction (Meyers / item 2)

  template< typename T >
  void func(ParmType param);

  func(expr)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)

  T         - template type

  ParamType - parameter type, basically the template type with certain
              adornments, e.g. const, reference, pointer, etc.

  expr      - expression type, the deducted type from the ParamType in the
              expression

  auto type deduction is usually the same as template type deduction,
  exception in cpp11:

  auto x1 = 13;       // template type deduction
  auto x2(13);        // template type deduction
  auto x3 = { 13 };   // calls std::initializer_list< int >
  auto x4{ 13 };      // calls std::initializer_list< int >

  x3 and x4 will have issues when passing an array, since
  std::initializer_list< int > won't be able to deal with arrays, this is fixed
  though in cpp14 and all four cases of initialization use template type
  deduction


  conclusion:

  - auto type deduction is usually the same as template type deduction, but auto
    type deduction assumes that a braced initializer represents a
    std::initializer_list, and template type deduction doesn't (in cpp11, solved
    in cpp14)

  - auto in a funciton return type or a lambda parameter iimplies template type
    deduction, not auto type deduction

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>

using namespace std;


// type investigation via polymorphism
void isConst(const int& arg) { cout << "const int&"; }
void isConst(int& arg) { cout << "int&"; }
void isConst(const int* arg) { cout << "const int*"; }
void isConst(int* arg) { cout << "int*"; }
void isConst(int&& arg) { cout << "int&&"; }


// definition
template< typename T >
void funcReference(T& param)
{
  cout << "\t -> funcReference<  ";
  isConst(param);
  cout << "  >";
}

template< typename T >
void funcConstReference(const T& param)
{
  cout << "\t -> funcReference<  ";
  isConst(param);
  cout << "  >";
}


template< typename T >
void funcPointer(T* param)
{
  cout << "\t -> funcPointer<  ";
  isConst(param);
  cout << "  >";
}

template< typename T >
void funcByValue(T param)
{
  cout << "\t -> funcByValue<  ";
  isConst(param);
  cout << "  >";
}

template< typename T >
void funcUniversalReference(T&& param)
{
  cout << "\t -> funcUniversalReference<  ";
  isConst(param);
  cout << "  >";
}

// return the array size of a passe-by-value passed array
template< typename T, std::size_t N >
constexpr std::size_t arraySize(T (&)[N]) noexcept
{
  return N;
}



int main(void)
{
  auto x = 27;
  const auto cx = x;
  const auto& rx = x;

  cout << "Auto Type Deduction" << endl;
  cout << endl;


  cout << "case 1: ParamType is a pointer or a reference type, but not a universal reference" << endl;

  // NOTE: template type here can be 'int&' or 'int' equally, the point is deduction forces
  // IMPORTANT: template type may be 'const int', but keep * or & as business of expr!
  cout << "Reference:" << endl;

  cout << "int x = 27;\t";
  funcReference(x); // reference: deduced int -> int&
  cout << "(x);";
  cout << endl;

  cout << "const int cx = x;";
  funcReference(cx); // reference: deduced const int -> const int&
  cout << "(cx);";
  cout << endl;

  cout << "const int& rx = x;";
  funcReference(rx); // reference: deduced const int& -> const int&
  cout << "(rx);";
  cout << endl;

  cout << endl;


  cout << "Const Reference:" << endl;

  cout << "int x = 27;\t";
  funcConstReference(x); // constreference: deduced int -> int&
  cout << "(x);";
  cout << endl;

  cout << "const int cx = x;";
  funcConstReference(cx); // constreference: deduced const int -> const int&
  cout << "(cx);";
  cout << endl;

  cout << "const int& rx = x;";
  funcConstReference(rx); // constreference: deduced const int& -> const int&
  cout << "(rx);";
  cout << endl;

  cout << endl;


  cout << "Pointer:" << endl;

  cout << "int x = 27;\t";
  funcPointer(&x); // pointer: deduced int -> int*
  cout << "(&x);";
  cout << endl;

  cout << "const int cx = x;";
  funcPointer(&cx); // pointer: deduced const int -> const int*
  cout << "(&cx);";
  cout << endl;

  cout << "const int& rx = x;";
  funcPointer(&rx); // pointer: deduced const int& -> const int*
  cout << "(&rx);";
  cout << endl;

  cout << endl;


  cout << "case 2: ParamType is a universal reference" << endl;

  cout << "Universal Reference:" << endl;

  cout << "int x = 27;\t";
  funcUniversalReference(x); // universa lreference: deduced int -> int&
  cout << "(x);";
  cout << endl;

  cout << "const int cx = x;";
  funcUniversalReference(cx); // universal reference: deduced const int -> const int&
  cout << "(cx);";
  cout << endl;

  cout << "const int& rx = x;";
  funcUniversalReference(rx); // universal reference: deduced const int& -> const int&
  cout << "(rx);";
  cout << endl;

  cout << endl;


  // special cases:
  cout << "Special Case: funcUniversalReference(13);";
  funcUniversalReference(13); // universal reference: deduced const int& -> const int&
  cout << "(rx); [actually: int&&]";
  cout << endl;

  cout << endl;


  cout << "case 3: ParamType is neither a pointer nor a reference - pass by value" << endl;

  cout << "byValue:" << endl;
  // pass by value means basically we are working on a copy, so if then the original
  // was const or not, is irrelevant when dealing with its copy

  cout << "int x = 27;\t";
  funcByValue(x); // byValue: deduced int -> int&
  cout << "(x); [actually: int]";
  cout << endl;

  cout << "const int cx = x;";
  funcByValue(cx); // byValue: deduced const int -> const int&
  cout << "(cx); [actually: int]";
  cout << endl;

  cout << "const int& rx = x;";
  funcByValue(rx); // byValue: deduced const int& -> const int&
  cout << "(rx); [actually: int]";
  cout << endl;

  cout << endl;


  cout << "Special case: array arguments" << endl;

  const int arr[] = { 1, 2, 3 };

  cout << "const int arr[] = { 1, 2, 3 };";
  funcByValue(arr); // byValue: deduced const int& -> const int&
  cout << "(rx); [but actually: the array was 'T (&)[N]']";
  cout << endl;

  // the difficulty is to figure out a function to determine the correct size of the array
  cout << "const int arr[]: arraySize() - ";
  cout << arraySize(arr);
  cout << endl;

  cout << "READY." << endl;
}

