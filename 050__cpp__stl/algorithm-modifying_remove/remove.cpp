// remove.cpp
/*
  modifying algorithm

  remove - remove elements equal to certain value
  remove_if - remove all elements for which a predicate is true

            ___         ___ ___
       +---+---+---+---+---+---+---+---+- -+
  arr: | 1 | 0 | 2 | 3 | 0 | 0 | 4 | 5 |   |
       +---+---+---+---+---+---+---+---+- -+
   |
   | remove(arr, arr+8, 0)
   |
  \|/   ___ ___ ___ ___ ___
       +---+---+---+---+---+---+---+---+- -+
  arr: | 1 | 2 | 3 | 4 | 5 | 0 | 4 | 5 |   |
       +---+---+---+---+---+---+---+---+- -+
                             stays!
                             a remvove_copy would simply
                             have omitted to copy
                             these 0, 4, 5

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm> // remove
#include <iostream>
#include <iterator> // ostream_iterator


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  int arr[] = {1, 0, 2, 3, 0, 0, 4, 5};
  cout << "arr: ";
  copy(arr, arr + 8, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "remove() - remove 0 and shrink to the front,\nptr points to the "
          "last element.\nThe remainder will be untouched.\n";
  int *ptr = remove(arr, arr + 8, 0);
  cout << "[arr; arr+8[ = \t";
  copy(arr, arr + 8, ostream_iterator< int >(cout, " "));
  cout << endl;
  cout << "[arr; ptr[ = \t";
  copy(arr, ptr, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "remove_if() - remove all odd numbers\n";
  ptr = remove_if(arr, ptr, bind2nd(modulus< int >(), 2));
  cout << "[arr, ptr[ = \t";
  copy(arr, ptr, ostream_iterator< int >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
