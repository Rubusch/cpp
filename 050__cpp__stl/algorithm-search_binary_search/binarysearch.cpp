// binarysearch.cpp
/*
  search algorithm

  binary_search - determine if an element exists in a certain range

  elements MUST be sorted before search algorithm!

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr_a[] = { 0, 1, 2, 2, 4, 4, 6 };
  copy(arr_a, arr_a+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "binary_search() for \'2\'\n";
  if(binary_search(arr_a, arr_a+7, 2)){
    cout << "\'2\' is contained\n";
  }
  cout << endl;

  cout << "second array to demonstrate greater< int >() on binary_search()\n";
  int arr_b[] = { 6, 4, 4, 3, 3, 1, 0 };
  copy(arr_b, arr_b+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "binary_search() for \'2\' in a descending sequence, using greater< int >()\n";
  if(!binary_search(arr_b, arr_b+7, 2, greater< int >())){
    cout << "\'2\' is not contained\n";
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
