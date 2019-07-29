/*
 * c++14: N3651 "Variable Templates"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3651.pdf
 *
 * compiler support:
 * gcc 5 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>

using namespace std;

/*
  applying the already existing template syntax to a variable.
*/
template<typename T>
constexpr T pi = T(3.1415926535897932385); // the variable template

/*
  use of such a variable in generic functions
*/
template<typename T>
T area_of_circle_with_radius(T radius)
{
  return pi<T> * radius * radius;
}

/*
  usage
*/
int main()
{
  int radint = 7;
  cout << "radius = " << radint << endl;
  cout << "area of circle = \n\t"
       << pi<int> << " * " << radint << "^2 = \n\t"
       << area_of_circle_with_radius<int>( radint ) << endl;

  double radouble = 1.23;
  cout << "radius = " << radouble << endl;
  cout << "area of circle = \n\t"
       << pi<double> << " * " << radouble << "^2 = \n\t"
       << area_of_circle_with_radius<double>( radouble ) << endl;

  return 0;
}
