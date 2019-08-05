// template.cpp
/*
  demonstrates the insert iterator "inserter" which allows to insert
  at any given place

  output:
  0 1 3 5 2 3 0 0

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr[] = { 1, 3, 5, 2, 3 };
  list< int > li(3U, 0);
  list< int >::iterator iter = li.begin();
  cout << endl;

  cout << "inserter\n";
  copy(arr, arr + 5, inserter(li, ++iter));
  cout << endl;

  cout << "output:\n";
  copy(li.begin(), li.end(), ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
