// partialsortcopy.cpp
/*
  sorting algorithm

  partial_sort_copy - copy and partially sort a range of elements

          ___ ___ ___ ___
         +---+---+---+---+---+---+---+- -+
  arr_a: | 3 | 1 | 0 | 6 | 2 | 5 | 4 |   |
         +---+---+---+---+---+---+---+- -+
   |
   | partial_sort_copy(arr_a, arr_a+7, arr_b, arr_b+4)
   |
  \|/     ___ ___ ___ ___
         +---+---+---+---+- -+  
  arr_b: | 0 | 1 | 2 | 3 |   |
         +---+---+---+---+- -+

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>


/*
  output
//*/
void display(int* arr_a, int size_a, int* arr_b, int size_b)
{
  std::cout << "arr_a: \t";
  copy(arr_a, arr_a+size_a, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl;
  std::cout << "arr_b: \t";
  copy(arr_b, arr_b+size_b, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl << std::endl;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = { 3, 1, 0, 6, 2, 5, 4 };
  int arr_b[4]; fill(arr_b, arr_b+4, 0);
  display(arr_a, 7, arr_b, 4);
  cout << endl;

  cout << "partial_sort_copy() - sort and copy to arr_b the first 4 elements\n";
  int* ptr = partial_sort_copy(arr_a, arr_a+7, arr_b, arr_b+4);
  cout << "first " << (ptr - arr_b) << " values are sorted\n";
  display(arr_a, 7, arr_b, 4);

  cout << "partial_sort_copy() - sort and copy the elements descending, copy the first 4 to the arr_b\n";
  ptr = partial_sort_copy(arr_a, arr_a+7, arr_b, arr_b+4, greater< int >());
  cout << "first " << (ptr - arr_b) << " values are sorted\n";
  display(arr_a, 7, arr_b, 4);  

  cout << "READY.\n";
  return 0;
}
