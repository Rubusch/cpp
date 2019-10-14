// equalrange.cpp
/*
  binary search algorithm

  equal_range - search for a range of elements that are all equal
  to a certain element

       +---+---+---+---+---+---+---+- -+
  arr: | 0 | 1 | 2 | 2 | 4 | 4 | 6 |   |
       +---+---+---+---+---+---+---+- -+
                 |       |
         equal_range(arr, arr+7, 2)

  elements MUST be sorted before search algorithm!

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = {0, 1, 2, 2, 4, 4, 6};
  copy(arr_a, arr_a + 7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "equal_range() returns a pair< const int*, const int* >\n";
  pair< const int *, const int * > pa = equal_range(arr_a, arr_a + 8, 2);
  cout << "\'2\' can be inserted in the range starting at "
       << (pa.first - arr_a) << " to " << (pa.second - arr_a) << endl;
  cout << "Hence, there are " << (pa.second - pa.first)
       << " elements with the value \'2\'\n";
  cout << endl;

  cout << "just another array to demonstrate equal_range() with greater()\n";
  const int arr_b[] = {6, 4, 4, 3, 3, 1, 0};
  copy(arr_b, arr_b + 7, ostream_iterator< int >(cout, " "));
  pa = equal_range(arr_b, arr_b + 7, 2, greater< int >());
  cout << "\'2\' can be inserted in the rane of " << (pa.first - arr_b)
       << " to " << (pa.second - arr_b) << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
