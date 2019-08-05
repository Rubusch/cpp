// rotate.cpp
/*
  modifying algorithm

  rotate - move the elements in some range to the left by some amount

  <dito>

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
  int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  copy(arr, arr+10, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "rotate()\n";
  rotate(arr, arr+3, arr+10);  // arr+3 shall be next index '0'
  copy(arr, arr+10, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
