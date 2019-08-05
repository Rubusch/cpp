// adjacentdifference.cpp
/*
  numeric algorithm

  adjacent_difference - compute the differences between adjacent elements in a range

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = { 490, 520, 480, 515 };
  int arr_diff[4]; fill(arr_diff, arr_diff+4, 0);
  cout << "arr: \t";
  copy(arr, arr+4, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "adjacent_difference() - difference to the predecessor, starting at 0\n";
  adjacent_difference(arr, arr+4, arr_diff);
  cout << "arr: \t";
  copy(arr, arr+4, ostream_iterator< int >(cout, " "));
  cout << "\ndiff: \t";
  copy(arr_diff, arr_diff+4, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
