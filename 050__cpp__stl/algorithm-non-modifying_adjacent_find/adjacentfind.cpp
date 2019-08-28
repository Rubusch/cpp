// adjacentfind.cpp
/*
  non-modifying algorithm

  adjacent_find - finds two items adjacent to each other

                ___ ___     ___ ___
       +---+---+---+---+---+---+---+- -+
  arr: | 1 | 2 | 3 | 3 | 1 | 2 | 2 |   |
       +---+---+---+---+---+---+---+- -+
                 |
       adjacent_find(arr, arr + 7)

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr[] = { 1, 2, 3, 3, 1, 2, 2 };
  cout << endl;

  cout << "adjacent_find() - first example\n";
  const int* ptr = adjacent_find(arr, arr + 7);
  if(ptr != arr + 7){
    cout << "the first two equal values start at index: " << (ptr - arr) << endl;
  }
  cout << endl;

  cout << "adjacent_find() - second example\n";
  ptr = adjacent_find(arr, arr+7, greater< int >());
  if(ptr != arr + 7){
    cout << "the first value greater than its next neighbor is at index: " << (ptr - arr) << endl;
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
