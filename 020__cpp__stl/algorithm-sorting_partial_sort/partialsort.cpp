// partialsort.cpp
/*
  sorting algorithm

  partial_sort - sort the first N elements of a range (heap-sort)

        ___ ___ ___ ___
       +---+---+---+---+---+---+---+- -+
  arr: | 3 | 1 | 0 | 6 | 2 | 5 | 4 |   |
       +---+---+---+---+---+---+---+- -+
   |
   | partial_sort(arr, arr+7)
   |
  \|/   ___ ___ ___ ___
       +---+---+---+---+---+---+---+- -+
  arr: | 0 | 1 | 2 | 3 | 6 | 5 | 4 |   |
       +---+---+---+---+---+---+---+- -+

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = { 3, 1, 0, 6, 2, 5, 4 };
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "partial_sort() - sort the first 4 elements in ascending order\n";
  partial_sort(arr, arr+4, arr+7);
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "partial_sort() - sort the rest in descending order\n";
  partial_sort(arr+4, arr+7, arr+7, greater< int >());
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
