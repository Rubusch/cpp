// count.cpp
/*
  non-modifying algorithm

  count - return the number of elements matching a given value
  count_if - return the number of elements for which a predicate is true

            ___             ___
       +---+---+---+---+---+---+---+- -+
  arr: | 1 | 2 | 3 | 4 | 3 | 2 | 1 |   |
       +---+---+---+---+---+---+---+- -+

  count(arr, arr+7, 2) == 2

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int arr[] = { 1, 2, 3, 4, 3, 2, 1 };
  cout << endl;

  cout << "2 is contained " << count(arr, arr+7, 2) << " times\n";
  cout << endl;

  cout << count_if(arr, arr+7, bind2nd(greater< int >(), 2)) << " values are greater than 2\n";
  cout << endl;

  cout << "READY.\n";
  return 0;
}
