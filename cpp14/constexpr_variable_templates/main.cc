/*
 * c++14: constexpr variable templates example
 *
 * compiler support
 * Clang 3.4 (ref. as "Relaxing requirements on constexpr functions", N3652) TODO check    
 *
 * author: Lothar Rubusch
 */
#include <iostream>

using namespace std;

/*
  applying the already existing template syntax to a variable.
*/
template<typename T>
constexpr T pi = T(3.1415926535897932385);

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
