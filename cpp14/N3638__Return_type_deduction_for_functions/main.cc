/*
 * c++14: N3638 "Return type deduction for normal functions"
 *
 * "Normally, decltype produces the type you expect."
 * Scott Meyers, Effective Modern C++, 2015, p.29
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3638.html
 *
 * compiler support:
 * gcc 4.8/4.9 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>
#include <vector>

using namespace std;

/*
  in general, auto in a function return type or lambda parameter implies
  "template type deduction", not "auto type deduction";

  the difference: auto type deduction assumes that a braced initializer,
  i.e. '(' and ')', represents a std::initializer_list<T>()
  (item 2, Meyers 2015)
 */
template<class T>
auto square(T n)
{
  /*
    compilers will deduce the return type from the function's implementation
    (item 3, Meyers 2015)
   */
  return n * n;
}



/*
  C++14 supports decltype(auto), which, like autho, deduces a type from its
  initializer, but it performs the type deduction using the decltype rules
  (item 3, 25, Meyers 2015)
 */
//*
// C++11
template<typename Container, typename Index>
auto
assignValue(Container&& cont, Index idx)
  ->decltype(forward<Container>(cont)[idx])
{
  // some checks...
  return forward<Container>(cont)[idx];
}
/*/
// C++14
template<typename Container, typename Index>
decltype(auto)
assignValue(Container&& cont, Index idx)
{
  // some checks...
  return forward<Container>(cont)[idx];
}
//*/


/*
  for lvalue expressions of type T other than names, decltype always reports a
  type of T&
 */
decltype(auto) func1()
{
  int x = 777;
  return x; // decltype(x) is int, func1 returns int
}

decltype(auto) func2()
{
  int x = 777;
  return (x); // decltype( (x) ) is int&, func2 returns int&
}


int main()
{
  cout << "general return type deduction:" << endl;
  int ires = square(3);
  cout << "square of 3 is " << ires << endl;
  double dres = square(1.4142);
  cout << "square of 1.4142 is " << dres << endl;
  cout << endl;

  cout << "assignment of returned rvalue becomes possible:" << endl;
  vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  assignValue(vec, 1) = 10; // assign to element of container
  for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
    cout << ' ' << *it;
  }
  cout << endl << endl;

  cout << "CAUTION at decltype return deduction and braces!" << endl;
  cout << "func1() returns int: "  << func1() << endl;
  cout << "func2() returns int&: " << &func2() << endl;
  cout << endl;

  return 0;
}

