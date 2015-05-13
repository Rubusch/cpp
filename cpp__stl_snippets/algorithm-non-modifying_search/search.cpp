// search.cpp
/*
  non-modifying algorithm

  search - search for a range of elements
          ___ ___
         +---+---+- -+
  arr_a: | 3 | 1 |   |
         +---+---+- -+

              ___ ___     ___ ___ 
         +---+---+---+---+---+---+---+- -+
  arr_b: | 5 | 3 | 1 | 4 | 3 | 1 | 5 |   |
         +---+---+---+---+---+---+---+- -+
               |
   search(arr_b, arr_b+7, arr_a, arr_a+2)

  (Kuhlins & Schader, 2003)
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
  const int arr_a[] = { 3, 1 };
  const int arr_b[] = { 5, 3, 1, 4, 3, 1, 5 };
  cout << endl;

  cout << "search() - example 1\n";
  const int* ptr = search( arr_b, arr_b+7, arr_a, arr_a+2);
  if(ptr != arr_b+7){
    cout << "arr_a occures the first time starting at index " << (ptr - arr_b) << endl;
  }
  cout << endl;

  cout << "search() - example 2\n";
  ptr = search(arr_b, arr_b+7, arr_a, arr_a+2, greater< int >());
  if(ptr != arr_b+7){
    cout << "after the following index all elements in arr_b will be greater than in arr_a "
         << (ptr - arr_b) << endl;
  }
  cout << endl;
 
  cout << "READY.\n";
  return 0;
}
