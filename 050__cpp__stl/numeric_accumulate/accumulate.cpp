// accumulate.cpp
/*
  numeric algorithm

  accumulate - sum up a range of elements

  resources: Kuhlins and Schader (2003)
//*/


#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = {3, 7, 6, 2, 4, 6};
  cout << "arr:\n";
  copy(arr, arr + 6, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "accumulate():\n" << accumulate(arr, arr + 6, 0) << endl << endl;

  cout << "accumulate() - using multiplies< int >():\n"
       << accumulate(arr, arr + 6, 1, multiplies< int >()) << endl
       << endl;

  cout << "READY.\n";
  return 0;
}
