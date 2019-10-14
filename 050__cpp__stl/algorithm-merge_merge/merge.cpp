// merge.cpp
/*
  shuffle algorithm

  merge - merge two sorted ranges

         +---+---+---+---+- -+            +---+---+---+- -+
  arr_a: | 0 | 2 | 2 | 4 |   |     arr_b: | 1 | 2 | 3 |   |
         +---+---+---+---+- -+            +---+---+---+- -+

    merge(arr_a, arr_a+4, arr_b, arr_b+3, vec.begin())

                                |
                                |
                               \|/

                      +---+---+---+---+- -+
                 vec: | 0 | 2 | 2 | 4 |   |
                      +---+---+---+---+- -+

  the ranges need to be sorted

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
  int arr_a[] = {0, 2, 2, 4};
  int arr_b[] = {1, 2, 3};
  vector< int > vec;
  vec.reserve(10);
  cout << "arr_a: \t";
  copy(arr_a, arr_a + 4, ostream_iterator< int >(cout, " "));
  cout << "\narr_b: \t";
  copy(arr_b, arr_b + 3, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "merge()\n";
  vector< int >::iterator iter =
      merge(arr_a, arr_a + 4, arr_b, arr_b + 3, vec.begin());
  cout << "arr_a and arr_b are merged in ascending order\n";
  copy(vec.begin(), iter, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "sort()\n";
  sort(arr_a, arr_a + 4, greater< int >());
  sort(arr_b, arr_b + 3, greater< int >());
  cout << "arr_a and arr_b merged in descending order\n";
  merge(arr_a, arr_a + 4, arr_b, arr_b + 3, ostream_iterator< int >(cout, " "),
        greater< int >());
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
