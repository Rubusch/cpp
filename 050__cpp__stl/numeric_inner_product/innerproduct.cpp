// innerproduct.cpp
/*
  numeric algorithm

  inner_produc - compute the inner product of two ranges of elements

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <numeric>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = { 1, 2, 3 };
  int arr_b[] = { 2, 6, 4 };
  cout << "arr_a: \t";
  copy(arr_a, arr_a+3, ostream_iterator< int >(cout, " "));
  cout << "\narr_b: \t";
  copy(arr_b, arr_b+3, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "inner_product() - scalar product:\n"
       << inner_product(arr_a, arr_a+3, arr_b, 0)
       << endl << endl;

  cout << "READY.\n";
  return 0;
}
