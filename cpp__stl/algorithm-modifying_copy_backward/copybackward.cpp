// copybackward.cpp
/*
  modifying algorithm

  copy_backward - copy a range of elements in backwards order

                 /----------------------->
                ___ ___ ___ ___ ___ ___
               +---+---+---+---+---+---+---+- -+
   +--    arr: | 0 | 1 | 3 | 5 | 2 | 4 | 6 |   |
   |           +---+---+---+---+---+---+---+- -+
   |
   |        copy_backward(arr, arr+6, arr+7)
   |             |
   |             |  ___ ___ ___ ___ ___ ___
   |           +---+---+---+---+---+---+---+- -+
   +--->  arr: | 0 | 0 | 1 | 3 | 5 | 2 | 4 |   |
               +---+---+---+---+---+---+---+- -+


  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <iterator>
#include <algorithm>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = { 0, 1, 3, 5, 2, 4, 6 };
  cout << endl;

  cout << "output before:\n";
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "copy_backward()\n";
  copy_backward(arr, arr+6, arr+7);
  cout << endl;

  cout << "output after:\n";
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
