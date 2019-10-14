// setunion.cpp
/*
  set algorithm

  set_union - computes the union of two sets

  arr_a: 2, 4, 6, 8
  arr_b: 1, 3, 5, 7

  set_union(arr_a, arr_a+4, arr_b, arr_b+4, vec.begin()

  -> vec: 1 2 3 4 5 6 7 8

  undefined behavior for unsorted input data!

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = {2, 4, 6, 8};
  int arr_b[] = {1, 3, 5, 7};
  vector< int > vec;
  vec.reserve(8);
  cout << "arr_a: \t";
  copy(arr_a, arr_a + 4, ostream_iterator< int >(cout, " "));
  cout << "\narr_b: \t";
  copy(arr_b, arr_b + 4, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "set_union()\n";
  vector< int >::iterator iter =
      set_union(arr_a, arr_a + 4, arr_b, arr_b + 4, vec.begin());
  cout << "vec: \t";
  copy(vec.begin(), iter, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
