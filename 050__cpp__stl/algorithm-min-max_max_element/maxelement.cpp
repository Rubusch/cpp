// maxelement.cpp
/*
  min/max algorithm

  max_element - returns the largest element in a range

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <iostream>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = {3, 2, 6, 4, 1, 5};
  copy(arr, arr + 6, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "max_element()\n";
  const int *ptr = max_element(arr, arr + 6);
  cout << "the biggest element is " << *ptr << ", with index: " << (ptr - arr)
       << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
