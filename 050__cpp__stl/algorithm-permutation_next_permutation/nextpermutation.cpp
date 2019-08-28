// nextpermutation.cpp
/*
  permutation algorithm

  next_permutation - generates the next greater lexicographic permutation of a range of elements

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
  int arr[] = { 1, 2, 3 };
  int* const ptr = arr + sizeof(arr) / sizeof(*arr);
  int idx = 0;
  copy(arr, arr+3, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  do{
    cout << ++idx << ". permutation: ";
    copy(arr, ptr, ostream_iterator< int >(cout, " "));
    cout << endl << endl;

  }while(next_permutation(arr, ptr));
  cout << endl;

  cout << "READY.\n";
  return 0;
}
