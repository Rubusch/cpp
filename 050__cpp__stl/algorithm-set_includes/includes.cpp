// includes.cpp
/*
  set algorithm

  includes - returns true if one set is a subset of another

  arr_a: 1 3 5
  arr_b: 0 1 2 3 4 5 6

  includes(arr_b, arr_b+7, arr_a, arr_a+3)
  -> true, arr_a is contained in arr_b

  undefined behavior for unsorted input data!

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>


void display(int *arr_a, int size_a, int *arr_b, int size_b)
{
  std::cout << "arr_a: \t";
  copy(arr_a, arr_a + size_a, std::ostream_iterator< int >(std::cout, " "));
  std::cout << "\narr_b: \t";
  copy(arr_b, arr_b + size_b, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl << std::endl;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = {1, 3, 5};
  int arr_b[] = {0, 1, 2, 3, 4, 5, 6};
  display(arr_a, 3, arr_b, 7);

  cout << "includes()\n";
  if (includes(arr_b, arr_b + 7, arr_a, arr_a + 3)) {
    cout << "arr_a is contained in arr_b\n";
  }
  cout << endl;

  cout << "includes() - descending order, here with less()\n";
  if (!includes(arr_b, arr_b + 7, arr_a, arr_a + 3, less< int >())) {
    cout << "arr_a is not contained in arr_b\n";
  } else {
    cout << "-> this message should appear ;)\n";
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
