// unique.cpp
/*
  modifying algorithm

  unique - remove a function to a range of elements

          ___     ___         ___         ___
         +---+---+---+---+---+---+---+---+---+---+- -+
  arr:   | 1 | 1 | 3 | 3 | 3 | 7 | 1 | 1 | 2 | 2 |   |
         +---+---+---+---+---+---+---+---+---+---+- -+
    |
    | unique(arr_a, arr_a+10)
    |
   \|/    ___ ___ ___ ___ ___
         +---+---+---+---+---+- will stay the same! -+
  arr:   | 1 | 3 | 7 | 1 | 2 | 7 | 1 | 1 | 2 | 2 |   |
         +---+---+---+---+---+- will stay the same! -+

  (Kuhlins & Schader, 2003)
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
  int arr[] = { 1, 1, 3, 3, 3, 7, 1, 1, 2, 2 };
  cout << "arr = \t ";
  copy(arr, arr+10, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "unique() - no duplicates!\n";
  int *ptr = unique(arr, arr+10);
  cout << "[arr, arr+10[ =\t ";
  copy(arr, arr+10, ostream_iterator< int >(cout, " "));
  cout << "\n[arr, ptr[ =\t ";
  copy(arr, ptr, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "unique() - applied with function greater()\n";
  ptr = unique(arr, ptr, greater< int >());
  cout << "[arr, ptr[ =\t ";
  copy(arr, ptr, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
