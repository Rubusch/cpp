/*
 * c++14: N3323 "Tweak to certain C++ contextual conversions"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3323.pdf
 *
 * compiler support:
 * gcc 4.9 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>
#include <cassert> // assert()

using namespace std;

/*
Listing 1 presents a modest template that wraps a value of arithmetic or pointer
type T, ensuring that the wrapped value will by default be initialized with T’s
zero value. Note in particular the pair of conversion operators (lines 13-14),
provided according to a well-established C++ coding pattern that allows const
and non-const objects to be treated differently.
 */
template< class T
          , class = typename std::enable_if<
		       std::is_arithmetic<T>::value
               || std::is_pointer<T>::value
	        >::type
		>
class Zero_init
{
public:
  Zero_init()      : val( static_cast<T>(0) ) {}
  Zero_init(T val) : val(val)                 {}
  operator T & ()       {return val;} // distinguishes non-const
  operator T   () const {return val;} // and const
private:
  T val;
};

int main()
{
  /*
	Listing 2 shows a simple use of this template. We observe (verified with two
	modern compilers) that most expressions (e.g. *p) have no compilation issue,
	but that the expression delete p produces diagnostics. More embarrassingly,
	the equivalent expressions delete (p+0) and delete +p are fine.
  */
  Zero_init<int* > p; assert( p == 0 );
  p = new int(7); assert( *p == 7 );

  delete p;     // error! => fixed in C++14
//  delete (p+0); // okay
//  delete +p;    // also okay


  /*
    Listing 3 shows another use of this template. Here, too, the arithmetic,
	assignment, and comparison operations work fine, yet the simple expression i
	is embarrassingly ill-formed (although the equivalent i+0 and +i are
	well-formed!) when used as the switch condition.
   * /
  Zero_init<int> i; assert( i == 0 );
  i = 7;            assert( i == 7 );

  switch( i   ) { ... } // error!
  switch( i+0 ) { ... } // okay
  switch( +i  ) { ... } // also okay
  //*/
}

