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



int main(void)
{
  int x = 27;
  const int cx = x;
  const int& rx = x;

  cout << "Template Type Deduction" << endl;
  cout << endl;


// case 1: ParamType is a pointer or a reference type, but not a universal reference

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


// case 2: ParamType is a universal reference

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
  cout << "(rx);";
  cout << endl;

  cout << endl;


// case 3: ParamType is neither a pointer nor a reference - pass by value

  cout << "byValue:" << endl;

  cout << "int x = 27;\t";
  funcByValue(x); // byValue: deduced int -> int&
  cout << "(x);";
  cout << endl;

  cout << "const int cx = x;";
  funcByValue(cx); // byValue: deduced const int -> const int&
  cout << "(cx);";
  cout << endl;

  cout << "const int& rx = x;";
  funcByValue(rx); // byValue: deduced const int& -> const int&
  cout << "(rx);";
  cout << endl;

  cout << endl;


  cout << "READY." << endl;
}
// TODO
