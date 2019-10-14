// search_n.cpp
/*
  non-modifying algorithm

  search_n - search for N consecutive copies of an element in some range

       +---+---+---+---+---+---+---+- -+
  arr: | 9 | 3 | 3 | 5 | 3 | 3 | 6 |   |
       +---+---+---+---+---+---+---+- -+
         |
      search_n( arr, arr+7, 2, 3)

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <functional>
#include <iostream>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr[] = {9, 3, 3, 5, 3, 3, 6};
  cout << endl;

  cout << "search_n() for 2 times 3 in the array\n";
  const int *ptr = search_n(arr, arr + 7, 2, 3);
  if (ptr != arr + 7) {
    cout << "2 times 3 occures the first time at index " << (ptr - arr) << endl;
  }
  cout << endl;

  cout << "search_n() for the first 3 in-a-row values, smaller than 7\n";
  ptr = search_n(arr, arr + 7, 3, 7, less< int >());
  if (ptr != arr + 7) {
    cout << "at index " << (ptr - arr)
         << " we have the first 3 values in-a-row, which are smaller than 7\n";
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
