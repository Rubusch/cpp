// setintersection.cpp
/*
  set algorithm

  set_intersection - computes the intersection of two sets

  arr_a: 2 4 6 8
  arr_b: 3 6 9

  set_intersection(arr_a, arr_a+4, arr_b, arr_b+3, vec.begin())
  -> vec: 6

  undefined behavior for unsorted input data!

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = { 2, 4, 6, 8 };
  int arr_b[] = { 3, 6, 9 };
  vector< int > vec; vec.reserve(7);
  cout << "arr_a: \t";
  copy(arr_a, arr_a+4, ostream_iterator< int >(cout, " "));
  cout << "\narr_b: \t";
  copy(arr_b, arr_b+3, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "set_intersection()\n";
  vector< int >::iterator iter = set_intersection(arr_a, arr_a+4, arr_b, arr_b+3, vec.begin());
  cout << "vec: \t";
  copy(vec.begin(), iter, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
