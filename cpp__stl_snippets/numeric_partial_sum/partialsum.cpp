// partialsum.cpp
/*
  numeric algorithm

  partial_sum - compute the partial sum of ranges of elements

  (Kuhlins & Schader, 2003)
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
  unsigned int arr[] = { 3, 1, 3, 0, 1, 3 };
  copy(arr, arr+6, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "partial_sum()\n";
  partial_sum(arr, arr+6, ostream_iterator< unsigned int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
