/*
  C++11 - template type deduction (Meyers / item 1)

  template< typename T >
  void func(ParmType param);

  func(expr)

  ---
  T         - template type
  ParamType - parameter type, basically the template type with certain adornments, e.g. const, reference, pointer, etc.
  expr      - expression type, the deducted type from the ParamType in the expression


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


// definition
template< typename T >
void funcReference(T& param)
{
  cout << "\t -> funcReference<  ";
  isConst(param);
  cout << "  >";
}

template< typename T >
void funcPointer(T* param)
{
  cout << "\t -> funcPointer< ";
  isConst(param);
  cout << "  >";
}

template< typename T >
void funcPlain(T param)
{
  cout << "\t -> funcPlain< ";
  isConst(param);
  cout << "  >";
}

template< typename T >
void funcUniversalReference(T&& param)
{
  cout << "\t -> funcUniversalReference< ";
  isConst(param);
  cout << "  >";
}



int main(void)
{
  int x = 27;
  const int cx = x;
  const int& rx = x;


  // template type here can be 'int&' or 'int' equally, the point is deduction forces

  // reference: int -> int&
  cout << "int x = 27;\t";
  funcReference<int&>(x);
  cout << "(x);";
  cout << endl;

  // reference: const int -> const int&
  cout << "const int cx = x;";
  funcReference<const int&>(cx);
  cout << "(cx);";
  cout << endl;

  // reference: const int& -> const int&
  cout << "const int& rx = x;";
  funcReference<const int&>(rx);
  cout << "(rx);";
  cout << endl;

  cout << endl;


  // pointer: int -> int&
  cout << "int x = 27;\t";
  funcPointer<int>(&x);
  cout << "(x);";
  cout << endl;

  // pointer: const int -> const int&
  cout << "const int cx = x;";
  funcPointer<const int>(&cx);
  cout << "(cx);";
  cout << endl;

  // pointer: const int& -> const int&
  cout << "const int& rx = x;";
  funcPointer<const int>(&rx);
  cout << "(rx);";
  cout << endl;

  cout << endl;


/*
  cout << "int x = 27; funcPlain(x)" << endl;
  funcPlain<int>(x);
  cout << "const int cx = x; funcPlain(cx)" << endl;
  funcPlain<int>(cx);
  cout << "const int& rx = x; funcPlain(rx)" << endl;
  funcPlain<int>(rx);

  funcReference<int>(x);
  funcReference<int>(cx);
  funcReference<int>(rx);
// */

  cout << "READY." << endl;
}
// TODO
