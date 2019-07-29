// equal.cpp
/*
  non-modifying algorithm

  equal - determine if two sets of elements are the same

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr_a[] = { 3, 2, 1, 4, 5, 6 };
  const int arr_b[] = { 3, 2, 1, 4, 3, 1, 2 };
  const int number = sizeof(arr_a) / sizeof(*arr_a);
  cout << endl;

  cout << "the first " << number << " elements of arr_a and arr_b are "
       << ((equal(arr_a, arr_a+number, arr_b)) ? "equal" : "not equal")
       << ".\n";
  cout << endl;

  cout << "are the first " << number
       << " elements of arr_a not smaller than the first elements of arr_b?\n"
       << ((equal(arr_a, arr_a+number, arr_b, greater_equal< int >())) ? "Yes" : "No")
       << ".\n";
  cout << endl;

  cout << "READY.\n";
  return 0;
}
