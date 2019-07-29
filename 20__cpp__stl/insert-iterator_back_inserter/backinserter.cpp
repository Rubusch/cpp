// backinserter.cpp
/*
  back_inserter demonstrated on vector<int>

  output:
  0 0 0 2 4 1 4 5 2 4 1 4 5

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>


/*
  main..
//*/
int main()
{
  using namespace std;

  const int arr[] = { 2, 4, 1, 4, 5 };

  cout << "init\n";
  vector< int > vec(3U, 0);
  cout << endl;

  cout << "back_insert_iterator< vector< int > >(vec)\n";
  copy(arr, arr + 5, back_insert_iterator< vector< int > >(vec));
  cout << endl;

  cout << "back_inserter(vec)\n";
  copy(arr, arr + 5, back_inserter(vec));
  cout << endl;

  cout << "print the content of the vector\n";
  copy(vec.begin(), vec.end(), ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
