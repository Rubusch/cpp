/*
  C++11 - prefer constexpr whenever possible (Meyers / item 15)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)

  literal   - a fixed value, thus compile time constant i.e. known at compile
  time (a literal type is a type defined at compile time)


  conclusion:

  - constexpr objects are const and are initialized with values known during
    compilation

  - constexpr functions can produce compile-time results when called with
    arguments whose values are known during compilation

  - constexpr objects and functions may be used in a wider range of contexts
    than non-constexpr objects and functions

  - constexpr is part of an object's or function's interface

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <array>
#include <iostream>

using namespace std;


class Point
{
private:
  double x, y;

public:
  constexpr Point(double xVal = 0, double yVal = 0) noexcept : x(xVal), y(yVal)
  {
  }

  constexpr double xValue() const noexcept { return x; }
  constexpr double yValue() const noexcept { return y; }

  /* // C++11
    void setX(double newX) noexcept { x = newX; }
    void setY(double newY) noexcept { y = newY; }
  /*/ // C++14
  constexpr void setX(double newX) noexcept { x = newX; }
  constexpr void setY(double newY) noexcept { y = newY; }
  // */
};

// extension, some other dependent class - initialization also shifted to
// compile time
constexpr Point midpoint(const Point &p1, const Point &p2) noexcept
{
  return {(p1.xValue() + p2.xValue()) / 2, (p1.yValue() + p2.yValue()) / 2};
}

//* // C++14: reflection
//
// return reflection of p with respect to the origin (C++14)
constexpr Point reflection(const Point &p) noexcept
{
  Point result;
  result.setX(-p.xValue()); // create non constant point
  result.setY(-p.yValue());
  return result; // return copy
}
// */


int main(void)
{
  cout << "given: " << endl;
  constexpr Point p1(1.2, 3.4);
  constexpr Point p2(5.6, 7.8);
  cout << "point1(" << p1.xValue() << ", " << p1.yValue() << ")" << endl;
  cout << "point2(" << p2.xValue() << ", " << p2.yValue() << ")" << endl;
  cout << endl;

  // using even derrived operations e.g. computation of midpoint (analytical
  // geometry) done at compile time
  constexpr auto mid = midpoint(p1, p2);
  cout << "mid(" << mid.xValue() << ", " << mid.yValue() << ")" << endl;
  cout << endl;

  constexpr auto reflected_mid = reflection(mid);
  cout << "reflected_mid(" << reflected_mid.xValue() << ", "
       << reflected_mid.yValue() << ")" << endl;
  cout << endl;


  cout << "READY." << endl;
}
