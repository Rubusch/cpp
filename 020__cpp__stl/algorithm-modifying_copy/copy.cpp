// copy.cpp
/*
  modifying algorithm

  copy - copy some range of elements to a new location

                 <-----------------------\
                ___ ___ ___ ___ ___ ___ ___
               +---+---+---+---+---+---+---+- -+
   +--    arr: | 0 | 1 | 3 | 5 | 2 | 4 | 6 |   |
   |           +---+---+---+---+---+---+---+- -+
   |
   |                         copy(arr+1, arr+7, arr)
   |                                     |
   |            ___ ___ ___ ___ ___ ___  |
   |           +---+---+---+---+---+---+---+- -+
   +--->  arr: | 1 | 3 | 5 | 2 | 4 | 6 | 6 |   |
               +---+---+---+---+---+---+---+- -+


  resources: Kuhlins and Schader (2003)
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

  cout << "copy()\n";
  copy(arr+1, arr+7, arr);
  cout << endl;

  cout << "output after:\n";
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
