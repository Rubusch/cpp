// mismatch.cpp
/*
  non-modifying algorithm

  mismatch - find the first position where two ranges differ

          ___ ___ ___ ___ ___
         +---+---+---+---+---+---+- -+
  arr_a: | 3 | 2 | 1 | 4 | 5 | 6 |   |
         +---+---+---+---+---+---+- -+
                           |
         mismatch(arr_a, arr_a+6, arr_b)
                           |
          ___ ___ ___ ___ ___
         +---+---+---+---+---+---+---+- -+
  arr_b: | 3 | 2 | 1 | 4 | 3 | 1 | 2 |   |
         +---+---+---+---+---+---+---+- -+

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
  const int arr_a[] = {3, 2, 1, 4, 5, 6};
  const int arr_b[] = {3, 2, 1, 4, 3, 1, 2};
  cout << endl;

  cout << "mismatch() - example 1\n";
  pair< const int *, const int * > pa = mismatch(arr_a, arr_a + 6, arr_b);
  if (pa.first != arr_a + 7) {
    cout << "at index " << (pa.first - arr_a)
         << " are the first values that are not equal: " << *(pa.first)
         << " and " << *(pa.second) << ".\n";
  }
  cout << endl;

  cout << "mismatch() - example 2\n";
  pa = mismatch(arr_a, arr_a + 6, arr_b, not_equal_to< int >());
  if (pa.first != arr_a + 6) {
    cout << "the first equal value has index " << (pa.first - arr_a) << ".\n";
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
