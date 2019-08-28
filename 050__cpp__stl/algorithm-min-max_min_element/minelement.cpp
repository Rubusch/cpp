// minelement.cpp
/*
  min/max algorithm

  min_element - returns the smalles element in a range

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = { 3, 2, 6, 4, 1, 5 };
  copy(arr, arr+6, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "min_element()\n";
  const int* ptr = min_element(arr, arr+6);
  cout << "the smalles element is " << *ptr
       << ", with index: " << (ptr - arr)
       << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
