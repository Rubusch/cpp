// partition.cpp
/*
  modifying algorithm

  partition - divide a range of elements into two groups
  stable_partition - divide elements into two groups while preserving their
relative order

                      ___         ___ ___
                 +---+---+---+---+---+---+---+- -+
   +----+-- arr: | 2 | 3 | 0 | 4 | 1 | 5 | 6 |   |
   |    |        +---+---+---+---+---+---+---+- -+
   |    |
   |    |         partition(arr, arr+7, bind2nd(modulus< int >(), 2))
   |    |                 |
   |    |    ___ ___ ___  |
   |   \|/  +---+---+---+---+---+---+---+- -+
   |   arr: | 5 | 3 | 1 | 4 | 0 | 2 | 6 |   |
   |        +---+---+---+---+---+---+---+- -+
   |
   |        stable_partition(arr, arr+7, bind2nd(modulus< int >(), 2))
   |                 |
   |    ___ ___ ___  |
  \|/  +---+---+---+---+---+---+---+- -+
  arr: | 3 | 1 | 5 | 2 | 0 | 4 | 6 |   |
       +---+---+---+---+---+---+---+- -+


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

  cout << "init: \t";
  int arr[] = {2, 3, 0, 4, 1, 5, 6};
  vector< int > vec(arr, arr + 7);
  copy(arr, arr + 7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "partition()\n";
  int *ptr = partition(arr, arr + 7, bind2nd(modulus< int >(), 2));
  cout << "odd values: \t";
  copy(arr, ptr, ostream_iterator< int >(cout, " "));
  cout << endl;
  cout << "even values: \t";
  copy(ptr, arr + 7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "stable_partition_() - order in case has changed..\n";
  vector< int >::iterator iter;
  iter = stable_partition(vec.begin(), vec.end(), bind2nd(modulus< int >(), 2));
  cout << "odd values: \t";
  copy(vec.begin(), iter, ostream_iterator< int >(cout, " "));
  cout << endl;
  cout << "even values: \t";
  copy(iter, vec.end(), ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
