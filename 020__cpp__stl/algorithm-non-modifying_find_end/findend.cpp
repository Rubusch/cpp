// findend.cpp
/*
  non-modifying algorithm

  find_end - find the last sequence of elements in a certain range

            ___ ___
           +---+---+- -+
  arr_a:   | 3 | 1 |   |
           +---+---+- -+

                ___ ___     ___ ___
           +---+---+---+---+---+---+---+- -+
  arr_b:   | 5 | 3 | 1 | 4 | 3 | 1 | 5 |   |
           +---+---+---+---+---+---+---+- -+
                             |
            find_end( arr_b, arr_b + 7, arr_a, arr_a + 2)

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
  const int arr_a[] = { 3, 1 };
  const int arr_b[] = { 5, 3, 1, 4, 3, 1, 5 };
  cout << endl;

  cout << "find last occurance using find_end():\n";
  const int *ptr = find_end(arr_b, arr_b + 7, arr_a, arr_a + 2);
  if(ptr != arr_b + 7){
    cout << "\tthe last occurance of pattern arr_a in arr_b\n\tstarts at index "
         << (ptr - arr_b)
         << endl;
  }
  cout << endl;

  cout << "find last occurance fulfilling a condition of an operation, e.g. greater in find_end():\n";
  ptr = find_end(arr_b, arr_b + 7, arr_a, arr_a + 2, greater< int >());
  if(ptr != arr_b + 7){
    cout << "\tlast segment in which all values contained in arr_b\n\tare greater than in arr_a, starts at index "
         << (ptr - arr_b)
         << endl;
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
