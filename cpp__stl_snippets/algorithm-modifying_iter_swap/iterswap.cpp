// iterswap.cpp
/*
  modifying algorithm

  iter_swap - swaps the elements pointed to by two iterators

                   val_a       val_b
                     |           |
               +---+---+---+---+---+---+- -+
   +--    arr: | 3 | 1 | 4 | 1 | 5 | 9 |   |
   |           +---+---+---+---+---+---+- -+
   |
   |              iter_swap(val_a, val_b)
   |
   |           +---+---+---+---+---+---+- -+
   +--->  arr: | 3 | 5 | 4 | 1 | 1 | 9 |   |
               +---+---+---+---+---+---+- -+
                     |           |
                   val_b       val_a

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
  int arr[] = { 3, 1, 4, 1, 5, 9 };
  int *pVal_a = arr+1
    , *pVal_b = arr+4;
  cout << endl;

  cout << "output before:\n";
  copy(arr, arr+6, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "iter_swap()\n";
  iter_swap(pVal_a, pVal_b);
  cout << endl;

  cout << "output after:\n";
  copy(arr, arr+6, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
