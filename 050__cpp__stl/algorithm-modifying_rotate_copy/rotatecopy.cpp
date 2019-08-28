// rotatecopy.cpp
/*
  modifying algorithm

  rotate_copy - copy and rotate a range of elements

  <dito>

  MUST NOT overlap!

  resources: Kuhlins and Schader (2003)
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
  int arr_a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int arr_b[10]; fill(arr_b, arr_b+10, 0);
  copy(arr_a, arr_a+10, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "rotate_copy() - rotate 3 elements, and copy to arr_b\n";
  int *ptr = rotate_copy(arr_a, arr_a+3, arr_a+10, arr_b); // the 3rd element becomes index '0'
  copy(arr_b, ptr, ostream_iterator< int >(cout, " ")); // ptr is the new end!
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
