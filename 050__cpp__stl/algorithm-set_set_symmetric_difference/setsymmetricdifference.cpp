// setsymmetricdifference.cpp
/*
  set algorithm

  set_symmetric_difference - computes the symmetric difference between two sets

  arr_a: 2 4 6 8
  arr_b: 3 6 9

  set_symmetric_difference(arr_a, arr_a+4, arr_b, arr_b+3, vec.begin())

  -> vec: 2 3 4 8 9
  (except 6 which is contained in both!)

  undefined behavior for unsorted input data!

  resources: Kuhlins and Schader (2003)
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
  int arr_b[] = { 9, 6, 3 };
  vector< int > vec; vec.reserve(7);
  cout << "arr_a: \t";
  copy(arr_a, arr_a+4, ostream_iterator< int >(cout, " "));
  cout << "\narr_b: \t";
  copy(arr_b, arr_b+3, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  sort(arr_a, arr_a+4); /* 2, 4, 6, 8 */
  sort(arr_b, arr_b+3); /* 3, 6, 9 */

  cout << "set_symmetric_difference()\n";
  vector< int >::iterator iter = set_symmetric_difference(arr_a, arr_a+4, arr_b, arr_b+3, vec.begin());
  cout << "vec: \t";
  copy(vec.begin(), iter, ostream_iterator< int >(cout, " "));
  cout << "\n\'6\' should be missing!\n" << endl;

  cout << "READY.\n";
  return 0;
}
