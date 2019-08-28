// reversecopy.cpp
/*
  modifying algorithm

  reverse_copy - create a copy of a range that is reversed

         +---+---+---+---+---+---+- -+
  arr_a: | 1 | 3 | 5 | 6 | 4 | 2 |   |
         +---+---+---+---+---+---+- -+
   |       |   |   +---+   |   |
   |       |   +-----------+   |
   |       +-------------------+
   |         reverse(arr, arr+6)
   |
  \|/
         +---+---+---+---+---+---+- -+
  arr_b: | 2 | 4 | 6 | 5 | 3 | 1 |   |
         +---+---+---+---+---+---+- -+


  Both MUST NOT overlap!

  resources: Kuhlins and Schader (2003)
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
  const int arr_a[] = { 1, 3, 5, 6, 4, 2 };
  int arr_b[6]; fill(arr_b, arr_b+6, 0);
  cout << "arr_a:\t ";
  copy(arr_a, arr_a+6, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "reverse_copy() - copying reversely to arr_b\n";
  int *ptr = reverse_copy(arr_a, arr_a+6, arr_b);
  cout << endl;

  cout << "arr_b:\t ";
  copy(arr_b, ptr, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
