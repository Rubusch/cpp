// reverse.cpp
/*
  modifying algorithm

  reverse - reverse elements in some range

       +---+---+---+---+---+---+- -+
  arr: | 1 | 3 | 5 | 6 | 4 | 2 |   |
       +---+---+---+---+---+---+- -+
   |     |   |   +---+   |   |
   |     |   +-----------+   |
   |     +-------------------+
   |     reverse(arr, arr+6)
   |
  \|/
       +---+---+---+---+---+---+- -+
  arr: | 2 | 4 | 6 | 5 | 3 | 1 |   |
       +---+---+---+---+---+---+- -+

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
  int arr[] = {1, 3, 5, 6, 4, 2};
  cout << "arr:\t ";
  copy(arr, arr + 6, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "reverse()\n";
  reverse(arr, arr + 6);
  cout << "arr:\t ";
  copy(arr, arr + 6, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
