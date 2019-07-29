// sort.cpp
/*
  sorting algorithm

  sort - sort a range into ascending order (quicksort)

       +---+---+---+---+---+---+---+- -+
  arr: | 3 | 1 | 0 | 6 | 2 | 5 | 4 |   |
       +---+---+---+---+---+---+---+- -+
   |
   | sort(arr, arr+7)
   |
  \|/
       +---+---+---+---+---+---+---+- -+
  arr: | 0 | 1 | 2 | 3 | 4 | 5 | 6 |   |
       +---+---+---+---+---+---+---+- -+

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = { 3, 1, 0, 6, 2, 5, 4 };
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "sort() - ascending order\n";
  sort(arr, arr+7);
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "sort() - descending order\n";
  sort(arr, arr+7, greater< int >());
  copy(arr, arr+7, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
