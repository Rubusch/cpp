// uniquecopy.cpp
/*
  modifying algorithm

  unique_copy - create a copy of some range of elements that contains no
consecutive duplicates

          ___     ___         ___     ___
         +---+---+---+---+---+---+---+---+---+---+- -+
  arr_a: | 1 | 1 | 3 | 3 | 3 | 2 | 2 | 7 | 1 | 1 |   |
         +---+---+---+---+---+---+---+---+---+---+- -+
    |
    | unique_copy(arr_a, arr_a+10, arr_b)
    |
   \|/    ___ ___ ___ ___ ___
         +---+---+---+---+---+---+---+---+---+---+- -+
  arr_b: | 1 | 3 | 2 | 7 | 1 |   |   |   |   |   |   |
         +---+---+---+---+---+---+---+---+---+---+- -+

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = {1, 1, 3, 3, 3, 1, 1, 7, 2, 2};
  int arr_b[10];
  fill(arr_b, arr_b + 10, 0);
  cout << "arr_a: ";
  copy(arr_a, arr_a + 10, ostream_iterator< int >(cout, " "));
  cout << "\narr_b: ";
  copy(arr_b, arr_b + 10, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "unique_copy() - copy every value in a unique way\n";
  int *ptr = unique_copy(arr_a, arr_a + 10, arr_b);
  copy(arr_b, arr_b + 10, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "unique_copy() - now use it with greater< int >(),\n"
       << "means only show elements that are greater than their predecessor\n";
  unique_copy(arr_b, ptr, ostream_iterator< int >(cout, " "), greater< int >());
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
