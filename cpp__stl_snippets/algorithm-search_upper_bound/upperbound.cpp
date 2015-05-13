// upperbound.cpp
/*
  binary search algorithm

  upper_bound - searches for the last possible location to 
  insert an element into an ordered range

                ___ ___
       +---+---+---+---+---+---+---+- -+
  arr: | 0 | 1 | 2 | 2 | 4 | 4 | 6 |   |
       +---+---+---+---+---+---+---+- -+
                         | 
            upper_bound(arr, arr+7, 2)

  elements MUST be sorted before search algorithm!

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;
  
  cout << "init\n";
  int arr_a[] = { 0, 1, 2, 2, 4, 4, 6 };
  cout << "arr: \t";
  copy(arr_a, arr_a+7, ostream_iterator< int >(cout, " "));
  cout << endl;
  cout << "idx: \t";
  for(int idx = 0; idx < 7; ++idx) cout << idx << " ";
  cout << endl << endl;

  cout << "upper_bound()\n";
  const int* ptr = upper_bound(arr_a, arr_a+7, 2);
  cout << "first index after the last occurrance of \'2\': " << (ptr - arr_a) << endl;
  cout << endl;
  
  cout << "init another array\n";
  int arr_b[] = { 6, 4, 4, 3, 3, 1, 0 };
  cout << "arr: \t";
  copy(arr_b, arr_b+7, ostream_iterator< int >(cout, " "));
  cout << endl;
  cout << "idx: \t";
  for(int idx = 0; idx < 7; ++idx) cout << idx << " ";
  cout << endl << endl;

  cout << "upper_bound() with greater()\n";
  ptr = upper_bound(arr_b, arr_b + 7, 2, greater< int >());
  cout << "arr: \t";
  copy(arr_b, arr_b+7, ostream_iterator< int >(cout, " "));
  cout << endl;
  cout << "idx: \t";
  for(int idx = 0; idx < 7; ++idx) cout << idx << " ";
  cout << endl << endl;

  cout << "\'2\' can be inserted at last after index: " << (ptr - arr_b) << endl;
  cout << endl;
  
  cout << "READY.\n";
  return 0;
}
