// nthelement.cpp
/*
  sorting algorithm

  nth-element - put one element in its sorted location and make sure that no elements 
  to its left are greater than any elements to its right (e.g. this is also a step in 
  quicksort)

       +---+---+---+---+---+---+---+---+---+---+- -+
  arr: | 6 | 8 | 5 | 0 | 3 | 7 | 2 | 4 | 9 | 1 |   |
       +---+---+---+---+---+---+---+---+---+---+- -+
   |
   | nth_element(arr, arr+4, arr+10)
   |
  \|/                   ___   
       +---+---+---+---+---+---+---+---+---+---+- -+
  arr: | 0 | 2 | 1 | 3 | 4 | 5 | 7 | 8 | 9 | 6 |   |
       +---+---+---+---+---+---+---+---+---+---+- -+

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
  int arr[] = { 6, 8, 5, 0, 3, 7, 2, 4, 9, 1 };
  copy(arr, arr+10, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "nth_element()\n"
       << "print the 4th element (which is actually 4) at ordered position,\n"
       << "all before is lower, all after is higher\n";
  nth_element(arr, arr+4, arr+10);
  copy(arr, arr+10, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
