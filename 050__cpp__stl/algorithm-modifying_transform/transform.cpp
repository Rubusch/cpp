// transform.cpp
/*
  modifying algorithm

  transform - applies a function to a range of elements

       +---+---+---+---+---+---+---+---+---+- -+
  arr: | 3 | 1 | 4 | 5 | 7 | 0 | 8 | 2 | 6 |   |
       +---+---+---+---+---+---+---+---+---+- -+

          |
          |  add +1 to all elements
          |  transform(arr, arr+9, arr, bind2nd(plus< int >(), 1))
         \|/

       +---+---+---+---+---+---+---+---+---+- -+
  arr: | 4 | 2 | 5 | 6 | 8 | 1 | 9 | 3 | 7 |   |
       +---+---+---+---+---+---+---+---+---+- -+

  resources: Kuhlins and Schader (2003)
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
  int arr[] = { 3, 1, 4, 5, 7, 0, 8, 2, 6 };
  cout << endl;

  cout << "arr: ";
  copy(arr, arr+9, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "transform() - add +1 to all elements\n";
  transform( arr, arr+9, arr, bind2nd(plus< int >(), 1));
  cout << endl;

  cout << "arr: ";
  copy(arr, arr+9, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "transform() - multiply all values with themselves, and print them out\narr: ";
  transform( arr, arr+9, arr, ostream_iterator< int >(cout, " "), multiplies< int >());
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
