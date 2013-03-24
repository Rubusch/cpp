// inplacemerge.cpp
/*
  shuffle algorithm

  inplace_merge - merge two ordered ranges in-place

       +---+---+---+---+---+---+---+---+---+---+- -+
  arr: | 0 | 2 | 2 | 3 | 4 | 1 | 1 | 3 | 5 | 5 |   |
       +---+---+---+---+---+---+---+---+---+---+- -+
   |
   |   inplace_merge(arr, arr+5, arr+10)
   |
  \|/
       +---+---+---+---+---+---+---+---+---+---+- -+
  arr: | 5 | 5 | 4 | 3 | 3 | 2 | 2 | 1 | 1 | 0 |   |
       +---+---+---+---+---+---+---+---+---+---+- -+

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>


/*
  main..
//*/
int main()
{
  using namespace std;
  
  cout << "init\n";
  int arr_a[] = { 0, 2, 2, 4, 1, 2, 3, 5, 5 };
  copy(arr_a, arr_a+9, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "inplace_merge() - ascending order\n";
  inplace_merge(arr_a, arr_a+4, arr_a+9);
  copy(arr_a, arr_a+9, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "init another array\n";
  int arr_b[] = { 5, 5, 3, 2, 1, 4, 2, 2, 0 };
  copy(arr_b, arr_b+9, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "using greater< int >() for descending order\n";
  inplace_merge(arr_b, arr_b+5, arr_b+9, greater< int >());
  copy(arr_b, arr_b+9, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
