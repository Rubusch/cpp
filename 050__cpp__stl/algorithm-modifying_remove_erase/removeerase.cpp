// removeerase.cpp
/*
  modifying algorithm

  remove - remove elements equal to certain value
  vector<T>::erase - removes elements from a vector

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = {1, 0, 2, 3, 0, 0, 4, 5};
  vector< int > vec(arr, arr + 8);
  vector< int >::iterator iter_rest = remove(vec.begin(), vec.end(), 0);
  cout << endl;

  cout << "at the start up - " << vec.size() << " elements:\n";
  copy(vec.begin(), vec.end(), ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "after remove - " << vec.size() << " elements:\n";
  copy(vec.begin(), vec.end(), ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  vec.erase(iter_rest, vec.end());
  cout << "after erase - " << vec.size() << " elements:\n";
  copy(vec.begin(), vec.end(), ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
