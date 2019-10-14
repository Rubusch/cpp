// removecopy.cpp
/*
  modifying algorithm

  remove_copy - copy a range of elements omitting those that match a certain
value remove_copy_if - create a copy of a range of elements, omitting any for
which a predicate is true

              ___         ___ ___
         +---+---+---+---+---+---+---+---+- -+
  arr_a: | 1 | 0 | 2 | 3 | 0 | 0 | 4 | 5 |   |
         +---+---+---+---+---+---+---+---+- -+
             |
             |  remove_copy(arr_a, arr_a+8, arr_b, 0)
             |
            \|/
         +---+---+---+---+---+- -+
  arr_b: | 1 | 2 | 3 | 4 | 5 |   |
         +---+---+---+---+---+- -+

  resources: Kuhlins and Schader (2003)
//*/


#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>


void display(int *arr, int size)
{
  copy(arr, arr + size, std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init:\n";
  int arr_a[] = {1, 0, 2, 3, 0, 0, 4, 5};
  int arr_b[8];
  fill(arr_b, arr_b + 8, 0);
  cout << "arr_a \t";
  display(arr_a, 8);
  cout << endl;

  cout << "remove_copy() - omit 0s, copy:\n";
  int *ptr = remove_copy(arr_a, arr_a + 8, arr_b, 0);
  cout << "arr_a \t";
  display(arr_a, 8);
  cout << "arr_b \t";
  display(arr_b, 5);
  cout << endl;

  cout << "ptr shows to the end of the range (last element that is not the "
          "omitted), the whole range looks like\nrange: \t";
  display(ptr - 5, 8); // ptr points to the end of the new range, -5 returns the
                       // "full" new copy
  cout << endl;

  cout << "remove_copy_if() - copy only the even numbers of arr_b to ptr:\n";
  remove_copy_if(arr_b, ptr, ostream_iterator< int >(cout, " "),
                 bind2nd(modulus< int >(), 2));
  cout << endl << endl;
  cout << "arr_a \t";
  display(arr_a, 8);
  cout << "arr_b \t";
  display(arr_b, 5);
  cout << endl;

  cout << "READY.\n";
  return 0;
}
