// inline.cpp
/*
  inlining is replacing the function call DIRECTLY with the code in the
  inline function.

  this demo here describes just one example where overloading of an operator*
  is handled by a inline friend function.

  - A function defined in the class'es header is considered to be translated as
  inline (a function actually, not a ctor, thogh here the technique is demonstrated
  with the ctors)

  - A function can be defined "inline" in the class explicitely (see operator=)

  - A function can be defined as "inline" outside a class (e.g. operator<< and
  operator*).

  Some issues with inline is that inlining can make debugging (tracing) more
  difficult. since the function calls to a inline function will be replaced
  directly by the inline function's code, it can increase the size of the
  program and can even lead to worse performance. Inlining is a recommendation
  to the compiler and not mandatory!
//*/

#include <iostream>

using namespace std;



// forwared decs
template<class T>
class Number;

// friend operators:
template<class T>
const Number<T> operator*(const Number<T>& lhs, const Number<T>& rhs);

template<class T>
ostream& operator<<(ostream& out, Number<T>& rhs);


/*
  some class representing a kind of number
//*/
template<class T>
class Number
{
private:
  T x_coord, y_coord;

public:
  // ctors
  Number()
    :x_coord(0), y_coord(0){};

  Number(const T& x, const T& y)
    :x_coord(x), y_coord(y) {};

  // operators
  inline Number<T>& operator=(const Number<T>& deepcpy);

  // friend functions
  friend ostream& operator<< <T>(ostream& out, Number<T>& rhs);
  friend const Number<T> operator* <T>(const Number<T>& lhs, const Number<T>& rhs); // XXX
};


template<class T>
inline
Number<T>& Number<T>::operator=(const Number<T>& deepcpy)
{
  if(this == &deepcpy) return *this;

  x_coord = deepcpy.x_coord;
  y_coord = deepcpy.y_coord;

  return *this;
}

/*
  The inline friend operator*

  Since we are using inline - this can be very tricky (Effective C++, Item 23 / Meyers).
  This implementation here is the most recommended version of handling a similar problem
  by using inline funcitons, via a ctor!
//*/
template<class T>
inline
const Number<T> operator*(const Number<T>& lhs, const Number<T>& rhs)
{
  return Number<T>(lhs.x_coord * rhs.x_coord, lhs.y_coord * rhs.y_coord);
}

template<class T>
inline
ostream& operator<<(ostream& out, Number<T>& rhs)
{
  return out << "\t::x = " << rhs.x_coord << "\n\t" << "::y = " << rhs.y_coord << "\n" << endl;
}



/*
  some main
//*/
int main()
{
  // init
  Number<int> a(3, 4), b(4, 3);

  cout << "a\n" << a << endl;
  cout << "b\n" << b << endl;
  cout << endl;

  Number<int> c = a * b;
  cout << "a * b == c\n" << c << endl;
  cout << endl;

  // done
  cout << "READY.\n";
  return 0;
}
