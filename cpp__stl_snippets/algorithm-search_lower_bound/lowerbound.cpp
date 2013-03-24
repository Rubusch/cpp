// lowerbound.cpp
/*
  binary search algorithm

  lower_bound - search for the first place that a value can be inserted 
  while preserving order

       +---+---+---+---+---+---+---+- -+
  arr: | 0 | 1 | 2 | 2 | 4 | 4 | 6 |   |
       +---+---+---+---+---+---+---+- -+
                 | 
       lower_bound(arr, arr+7, 2), first occurrance of '2'

  elements MUST be sorted before search algorithm!
  
  as written in the specification to lower_bound, the result means also 
  !greater< int >()(*ptr, 2)

  thus meant here is equivalency and NOT equality!

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
  int arr_a[] = { 0, 1, 2, 2, 4, 4, 6 };
  copy(arr_a, arr_a+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "lower_bound()\n";
  const int* const ptr1 = lower_bound(arr_a, arr_a+7, 2);
  if((ptr1 != arr_a+7) && (*ptr1 == 2)){
    cout << "found first occurrance for 2 at index: " << (ptr1 - arr_a) << endl;
  }
  cout << endl;

  cout << "insert value in descending ordered array\n"
       << "init another array of 8 elements with 7 elements\n"
       << "(one additional for the new element)\n";
  int arr_b[8] = { 6, 4, 4, 3, 3, 1, 0 };
  copy(arr_b, arr_b+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;
  
  int* const ptr2 = lower_bound(arr_b, arr_b+7, 2, greater< int >());
  cout << "insert \'2\' at index (ascending, again): " << (ptr2 - arr_b) << endl;
  *copy_backward(ptr2, arr_b+7, arr_b+8) = 2;
  copy(arr_b, arr_b+8, ostream_iterator< int >(cout, " "));
  cout << endl << endl;
  
  cout << "READY.\n";
  return 0;
}
